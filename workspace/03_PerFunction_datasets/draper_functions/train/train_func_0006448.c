waitForTask() {
  FXTRACE((60,"GMAudioScrobbler::waitForTask\n"));
  if (timeout>0) {
#if FOXVERSION < FXVERSION(1,7,0)
    FXlong wakeuptime = FXThread::time()+((FXlong)timeout*1000000000LL);
#else
    FXlong wakeuptime = ((FXlong)timeout*1000000000LL);
    FXlong start      = FXThread::time();
#endif
    while(1) {
#if FOXVERSION < FXVERSION(1,7,0)
      FXTRACE((60,"GMAudioScrobbler::waitForTask => %ld\n",timeout));
#else
      FXTRACE((60,"GMAudioScrobbler::waitForTask => %ld\n",wakeuptime));
#endif
      mutex_task.lock();
      if (!condition_task.wait(mutex_task,wakeuptime)){
        mutex_task.unlock();
        return true;
        }
      else  {
        mutex_task.unlock();
        FXMutexLock lock(mutex_data);

        if (flags&FLAG_SHUTDOWN)
          return false;

        if (flags&FLAG_NETWORK) {
          flags&=~FLAG_NETWORK;
          return true;
          }

#if FOXVERSION > FXVERSION(1,7,0)
        FXlong now  = FXThread::time();
        wakeuptime -= (now - start);
        start       = now;


        if (wakeuptime<=0)
          return true;
#endif
        FXTRACE((60,"GMAudioScrobbler::waitForTask => reset\n"));
        }
      }
    }
  else {
    mutex_task.lock();
    condition_task.wait(mutex_task);
    mutex_task.unlock();
    }
  return true;
  }
