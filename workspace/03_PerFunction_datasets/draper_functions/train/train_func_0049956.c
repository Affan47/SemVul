_get_job_comment(struct job_record *job_ptr,
			char *buffer, int buf_size)
{
	int size, sharing = 0;
	char *field_sep = "";


	size = snprintf(buffer, buf_size, "COMMENT=\"");


	if (job_ptr->details && job_ptr->details->dependency) {

		size += snprintf((buffer + size), (buf_size - size),
			"DEPEND=%s", job_ptr->details->dependency);
		field_sep = "?";
	}


	if (cr_enabled)	{
		if (job_ptr->part_ptr &&
		    (job_ptr->part_ptr->max_share == 0))
			sharing = 0;
		else if (job_ptr->details && job_ptr->details->shared)
			sharing = 1;
	} else if (job_ptr->part_ptr) {
		if (job_ptr->part_ptr->max_share & SHARED_FORCE)
			sharing = 1;
		else if ((job_ptr->part_ptr->max_share > 1) &&
		         (job_ptr->details) && (job_ptr->details->shared))
			sharing = 1;
	}
	if (sharing) {

		size += snprintf((buffer + size), (buf_size - size),
			"%sNACCESSPOLICY:shared", field_sep);
		field_sep = "?";
	}


	if (job_ptr->details && (job_ptr->details->ntasks_per_node != 0)) {
		size += snprintf((buffer + size), (buf_size - size),
			"%sTPN:%u", field_sep,
			job_ptr->details->ntasks_per_node);
		field_sep = "?";
	}


	if (job_ptr->details && job_ptr->details->requeue) {
		size += snprintf((buffer + size), (buf_size - size),
			"%sJOBFLAGS:RESTARTABLE", field_sep);
		field_sep = "?";
	}


	if (job_ptr->comment && job_ptr->comment[0]) {
		size += snprintf((buffer + size), (buf_size - size),
			"%s%s", field_sep, job_ptr->comment);
		field_sep = "?";
	}

	size += snprintf((buffer + size), (buf_size - size), "\";");
}
