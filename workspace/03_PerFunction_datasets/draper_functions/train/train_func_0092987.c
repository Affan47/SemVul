_process_terminated(List job_list, char *f[], int lc,
				int show_full, int len)
{
	filetxt_job_rec_t *job = NULL;
	filetxt_job_rec_t *temp = NULL;

	_parse_line(f, (void **)&temp, len);
	job = _find_job_record(job_list, temp->header, JOB_TERMINATED);
	if (!job) {
		job = _create_filetxt_job_rec(temp->header);
		job->jobname = xstrdup("(unknown)");
		debug("Note: JOB_TERMINATED record for job "
		      "%u preceded "
		      "other job records at line %d\n",
		      temp->header.jobnum, lc);
	} else if (job->job_terminated_seen) {
		if (temp->status == JOB_NODE_FAIL) {

			debug("Note: Duplicate JOB_TERMINATED "
			      "record (nf) for job %u at "
			      "line %d\n",
			      temp->header.jobnum, lc);


			job->status = temp->status;
			goto finished;
		}

		fprintf(stderr,
			"Conflicting JOB_TERMINATED record (%s) for "
			"job %u at line %d -- ignoring it\n",
			job_state_string(temp->status),
			job->header.jobnum, lc);
		goto finished;
	}
	job->job_terminated_seen = 1;
	job->elapsed = temp->elapsed;
	job->end = temp->header.timestamp;
	job->status = temp->status;
	job->requid = temp->requid;
	job->exitcode = temp->exitcode;
	if(list_count(job->steps) > 1)
		job->track_steps = 1;
	job->show_full = show_full;

finished:
	_destroy_filetxt_job_rec(temp);
}
