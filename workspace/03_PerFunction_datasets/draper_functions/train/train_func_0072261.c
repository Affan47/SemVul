jobcomp_destroy_job(void *object)
{
	jobcomp_job_rec_t *job = (jobcomp_job_rec_t *)object;
	if (job) {
		xfree(job->partition);
		xfree(job->start_time);
		xfree(job->end_time);
		xfree(job->uid_name);
		xfree(job->gid_name);
		xfree(job->nodelist);
		xfree(job->jobname);
		xfree(job->state);
		xfree(job->timelimit);
		xfree(job->blockid);
		xfree(job->connection);
		xfree(job->reboot);
		xfree(job->rotate);
		xfree(job->geo);
		xfree(job->bg_start_point);
		xfree(job);
	}
}
