release()
  {
# ifndef RES_INIT_THREADSAFE
    QMutexLocker locker(&mutex);
    if (--useCount == 0)
      {
	if (shouldResInit())
	  callResInit();


	cond.wakeAll();
      }
# else

# endif
  }
