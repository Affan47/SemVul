_wait_for_any_task(slurmd_job_t *job, bool waitflag)
{
	slurmd_task_info_t *t = NULL;
	int status;
	pid_t pid;
	int completed = 0;
	jobacctinfo_t *jobacct = NULL;
	struct rusage rusage;
	do {
		pid = wait3(&status, waitflag ? 0 : WNOHANG, &rusage);
		if (pid == -1) {
			if (errno == ECHILD) {
				debug("No child processes");
				if (completed == 0)
					completed = -1;
				goto done;
			} else if (errno == EINTR) {
				debug("wait3 was interrupted");
				continue;
			} else {
				debug("Unknown errno %d", errno);
				continue;
			}
		} else if (pid == 0) {
			goto done;
		}


		jobacct = jobacct_gather_remove_task(pid);
		if (jobacct) {
			jobacctinfo_setinfo(jobacct,
					    JOBACCT_DATA_RUSAGE, &rusage);
			jobacctinfo_aggregate(job->jobacct, jobacct);
			jobacctinfo_destroy(jobacct);
		}


		if ((t = job_task_info_by_pid(job, pid))) {
			completed++;
			_log_task_exit(t->gtid, pid, status);

			t->exited  = true;
			t->estatus = status;
			job->envtp->env = job->env;
			job->envtp->procid = t->gtid;
			job->envtp->localid = t->id;

			job->envtp->distribution = -1;
			job->envtp->batch_flag = job->batch;
			setup_env(job->envtp, false);
			job->env = job->envtp->env;
			if (job->task_epilog) {
				_run_script_as_user("user task_epilog",
						    job->task_epilog,
						    job, 5, job->env);
			}
			if (conf->task_epilog) {
				char *my_epilog;
				slurm_mutex_lock(&conf->config_mutex);
				my_epilog = xstrdup(conf->task_epilog);
				slurm_mutex_unlock(&conf->config_mutex);
				_run_script_as_user("slurm task_epilog",
						    my_epilog,
						    job, -1, job->env);
				xfree(my_epilog);
			}
			job->envtp->procid = t->id;

			if (spank_task_exit (job, t->id) < 0) {
				error ("Unable to spank task %d at exit",
				       t->id);
			}
			post_term(job);
		}

	} while ((pid > 0) && !waitflag);

done:
	return completed;
}
