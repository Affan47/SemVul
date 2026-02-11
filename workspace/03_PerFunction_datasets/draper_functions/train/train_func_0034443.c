select_p_select_jobinfo_sprint(select_jobinfo_t *jobinfo,
					    char *buf, size_t size, int mode)
{

	if (buf == NULL) {
		error("select/cray jobinfo_sprint: buf is null");
		return NULL;
	}

	if ((mode != SELECT_PRINT_DATA)
	    && jobinfo && (jobinfo->magic != JOBINFO_MAGIC)) {
		error("select/cray jobinfo_sprint: jobinfo magic bad");
		return NULL;
	}

	if (jobinfo == NULL) {
		if (mode != SELECT_PRINT_HEAD) {
			error("select/cray jobinfo_sprint: jobinfo bad");
			return NULL;
		}
	}

	switch (mode) {


	case SELECT_PRINT_HEAD:
		snprintf(buf, size, "ALPS");
		break;
	case SELECT_PRINT_DATA:
		if (jobinfo->reservation_id)
			snprintf(buf, size, "%4u", jobinfo->reservation_id);
		else
			snprintf(buf, size, "%4s", "none");
		break;
	case SELECT_PRINT_MIXED:
		if (jobinfo->reservation_id)
			snprintf(buf, size, "resId=%u",
				 jobinfo->reservation_id);
		else
			snprintf(buf, size, "resId=none");
		break;
	case SELECT_PRINT_RESV_ID:
		snprintf(buf, size, "%u", jobinfo->reservation_id);
		break;
	default:
		other_select_jobinfo_sprint(jobinfo->other_jobinfo, buf,
					    size, mode);
		break;
	}

	return buf;
}
