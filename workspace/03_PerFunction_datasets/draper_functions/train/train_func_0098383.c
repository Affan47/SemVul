slurmdb_destroy_job_rec(void *object)
{
	slurmdb_job_rec_t *job = (slurmdb_job_rec_t *)object;
	if (job) {
		xfree(job->account);
		xfree(job->blockid);
		xfree(job->cluster);
		xfree(job->derived_es);
		xfree(job->jobname);
		xfree(job->partition);
		xfree(job->nodes);
		if(job->steps) {
			list_destroy(job->steps);
			job->steps = NULL;
		}
		xfree(job->user);
		xfree(job->wckey);
		xfree(job);
	}
}
