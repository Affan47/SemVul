Terminate()
{
	AddDebugLogLineN(logThreads, wxT("Terminating scheduler"));
	CThreadScheduler* ptr = NULL;

	{
		wxMutexLocker lock(s_lock);


		ptr = s_scheduler;
		s_running = false;
		s_terminated = true;
		s_scheduler = NULL;
	}

	delete ptr;
	AddDebugLogLineN(logThreads, wxT("Scheduler terminated"));
}
