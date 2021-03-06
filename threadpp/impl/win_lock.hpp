//
//  win_lock.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//
#ifndef __threadpp__win_lock__hpp__
#define __threadpp__win_lock__hpp__

#include "win_thread.h"
#include "../threadpp_assert.h"
#include "stdio.h"
namespace threadpp{
    
    static inline void test_error(const char* title)
    {
        DWORD e = GetLastError();
        ASSERT(e==0,"%s failed,error:%d",title,e);
    }
    
    inline win_lock::win_lock():_owner(0),_count(0)
    {
        SetLastError(0);
        InitializeCriticalSection(&_mutex);
        InitializeConditionVariable(&_cond);
        test_error("init");
    }
    
    inline win_lock::~win_lock()
    {
        DeleteCriticalSection(&_mutex);
    }
    
    inline void win_lock::lock()
    {
        SetLastError(0);
        
        EnterCriticalSection(&_mutex);
        
        test_error("lock");
    }
    
    inline void win_lock::unlock()
    {
        SetLastError(0);
        LeaveCriticalSection(&_mutex);
        test_error("unlock");
    }
    
    inline void win_lock::wait()
    {
        SetLastError(0);
        SleepConditionVariableCS(&_cond,&_mutex,0xFFFFFFFF);
        test_error("wait");
    }
    
    inline void win_lock::wait(unsigned long millisecs)
    {
        SetLastError(0);
        SleepConditionVariableCS(&_cond,&_mutex,millisecs);
        DWORD e = GetLastError();
        ASSERT(e==0||e == ERROR_TIMEOUT,"timed wait failed,error:",e);
    }
    
    inline void win_lock::notify()
    {
        SetLastError(0);
        WakeConditionVariable(&_cond);
        test_error("notify");
    }
    
    inline void win_lock::notify_all()
    {
        SetLastError(0);
        WakeAllConditionVariable(&_cond);
        test_error("notify all");
    }
}
#endif