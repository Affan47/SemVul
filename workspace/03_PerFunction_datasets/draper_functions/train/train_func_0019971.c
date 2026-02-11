AddTask(CThreadTask* task, bool overwrite)
{
	wxMutexLocker lock(s_lock);


	if (s_terminated) {
		AddDebugLogLineN(logThreads, wxT("Task discarded: ") + task->GetDesc());
		delete task;
		return false;
	} else if (s_scheduler == NULL) {
		s_scheduler = new CThreadScheduler();
		AddDebugLogLineN(logThreads, wxT("Scheduler created."));
	}

	return s_scheduler->DoAddTask(task, overwrite);
}
