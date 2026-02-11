get_job(private_processor_t *this, worker_thread_t *worker)
{
	int i, reserved = 0, idle;

	idle = get_idle_threads_nolock(this);

	for (i = 0; i < JOB_PRIO_MAX; i++)
	{
		if (reserved && reserved >= idle)
		{
			DBG2(DBG_JOB, "delaying %N priority jobs: %d threads idle, "
				 "but %d reserved for higher priorities",
				 job_priority_names, i, idle, reserved);

			return FALSE;
		}
		if (this->working_threads[i] < this->prio_threads[i])
		{
			reserved += this->prio_threads[i] - this->working_threads[i];
		}
		if (this->jobs[i]->remove_first(this->jobs[i],
										(void**)&worker->job) == SUCCESS)
		{
			worker->priority = i;
			return TRUE;
		}
	}
	return FALSE;
}
