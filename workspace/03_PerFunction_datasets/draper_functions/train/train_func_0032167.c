job_modify(struct job_descriptor *job_desc,
		      struct job_record *job_ptr, uint32_t submit_uid)
{
	char *tok;

	xassert(job_ptr);

	_xlate_dependency(job_desc, submit_uid, job_ptr->job_id);

	if (job_desc->std_out) {
		if (job_ptr->comment)
			xstrcat(job_ptr->comment, ",");
		xstrcat(job_ptr->comment, "stdout=");
		if ((job_desc->std_out[0] != '/') && job_ptr->details &&
		    job_ptr->details->work_dir) {
			xstrcat(job_ptr->comment, job_ptr->details->work_dir);
			xstrcat(job_ptr->comment, "/");
		}
		tok = strstr(job_desc->std_out, "%j");
		if (tok) {
			char buf[16], *tok2;
			char *tmp = xstrdup(job_desc->std_out);
			tok2 = strstr(tmp, "%j");
			tok2[0] = '\0';
			snprintf(buf, sizeof(buf), "%u", job_ptr->job_id);
			xstrcat(tmp, buf);
			xstrcat(tmp, tok + 2);
			xstrcat(job_ptr->comment, tmp);
			xfree(tmp);
		} else {
			xstrcat(job_ptr->comment, job_desc->std_out);
		}
		xfree(job_desc->std_out);
	}

	return SLURM_SUCCESS;
}
