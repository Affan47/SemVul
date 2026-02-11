WaitOnEvent(int timeoutMs)
{
#ifdef _WIN32


	WaitForSingleObjectEx(eventList,timeoutMs,FALSE);


#else


	isSignaledMutex.Lock();
	if (isSignaled==true)
	{
		isSignaled=false;
		isSignaledMutex.Unlock();
		return;
	}
	isSignaledMutex.Unlock();


		struct timespec   ts;

		int rc;
		struct timeval    tp;
		rc =  gettimeofday(&tp, NULL);
		ts.tv_sec  = tp.tv_sec;
		ts.tv_nsec = tp.tv_usec * 1000;


		while (timeoutMs > 30)
		{


			ts.tv_nsec += 30*1000000;
			if (ts.tv_nsec >= 1000000000)
			{
			        ts.tv_nsec -= 1000000000;
			        ts.tv_sec++;
			}


            pthread_mutex_lock(&hMutex);
			pthread_cond_timedwait(&eventList, &hMutex, &ts);
            pthread_mutex_unlock(&hMutex);

			timeoutMs-=30;

			isSignaledMutex.Lock();
			if (isSignaled==true)
			{
				isSignaled=false;
				isSignaledMutex.Unlock();
				return;
			}
			isSignaledMutex.Unlock();
		}


		ts.tv_nsec += timeoutMs*1000000;
		if (ts.tv_nsec >= 1000000000)
		{
		        ts.tv_nsec -= 1000000000;
		        ts.tv_sec++;
		}

		pthread_mutex_lock(&hMutex);
		pthread_cond_timedwait(&eventList, &hMutex, &ts);
        pthread_mutex_unlock(&hMutex);

		isSignaledMutex.Lock();
		isSignaled=false;
		isSignaledMutex.Unlock();

#endif
}
