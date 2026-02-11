GetThreadFromPool()
{
	Mutex::ScopedLock lock( dequeMutex );


	if (idleThreads.size() == 0)
	{

		bool foundIdleThread = false;
		std::deque<PooledThread*>::iterator iter;
		for (iter = busyThreads.begin(); iter < busyThreads.end(); iter++)
		{
			PooledThread* threadPtr = *iter;
			if ( !threadPtr->IsRunning() )
			{
				busyThreads.erase(iter);
				idleThreads.push_back(threadPtr);
				foundIdleThread = true;
			}
		}

		if ( !foundIdleThread )
		{
			idleThreads.push_back( new CLAM::PooledThread(this, mIsRealtime) );
		}
	}

	PooledThread* threadPtr = idleThreads.at(0);
	idleThreads.pop_front();
	busyThreads.push_back(threadPtr);

	return threadPtr;
}
