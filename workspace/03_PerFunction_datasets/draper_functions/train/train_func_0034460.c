_find_job_record(List job_list,
					   filetxt_header_t header,
					   int type)
{
	filetxt_job_rec_t *job = NULL;
	ListIterator itr = list_iterator_create(job_list);

	while((job = (filetxt_job_rec_t *)list_next(itr)) != NULL) {
		if (job->header.jobnum == header.jobnum) {
			if(job->header.job_submit == 0 && type == JOB_START) {
				list_remove(itr);
				_destroy_filetxt_job_rec(job);
				job = NULL;
				break;
			}

			if(job->header.job_submit == BATCH_JOB_TIMESTAMP) {
				job->header.job_submit = header.job_submit;
				break;
			}

			if(job->header.job_submit == header.job_submit)
				break;
			else {


				job->jobnum_superseded = 1;
			}
		}
	}
	list_iterator_destroy(itr);
	return job;
}
