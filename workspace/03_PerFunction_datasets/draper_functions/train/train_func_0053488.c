_destroy_filetxt_job_rec(void *object)
{
	filetxt_job_rec_t *job = (filetxt_job_rec_t *)object;
	if (job) {
		if(job->steps)
			list_destroy(job->steps);
		_free_filetxt_header(&job->header);
		xfree(job->jobname);
		xfree(job->account);
		xfree(job->nodes);
		xfree(job);
	}
}
