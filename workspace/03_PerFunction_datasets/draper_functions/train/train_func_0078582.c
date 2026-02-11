pdebug_wake_process(stepd_step_rec_t *job, pid_t pid)
{
	if ((job->task_flags & TASK_PARALLEL_DEBUG) && (pid > (pid_t) 0)) {
		if (_pid_to_wake(pid)) {
			if (kill(pid, SIGCONT) < 0)
				error("kill(%lu): %m", (unsigned long) pid);
			else
				debug("woke pid %lu", (unsigned long) pid);
		} else {
			debug("pid %lu not stopped", (unsigned long) pid);
		}
	}
}
