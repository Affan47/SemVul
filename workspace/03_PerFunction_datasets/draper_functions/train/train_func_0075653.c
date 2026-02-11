on_ra_proc_query_name(ProcTrack* p)
{
	static char proc_name[MAX_PROC_NAME];
	lrmd_op_t* op = NULL;
	lrmd_rsc_t* rsc = NULL;
	const char* op_type = NULL;

	LRMAUDIT();
	op = (lrmd_op_t*)(proctrack_data(p));
	if (NULL == op || op->exec_pid == 0) {
		return "*unknown*";
	}

	op_type = ha_msg_value(op->msg, F_LRM_OP);
	rsc = lookup_rsc(op->rsc_id);
	if (rsc == NULL) {
		snprintf(proc_name
		, MAX_PROC_NAME
		, "unknown rsc(%s):%s maybe deleted"
		, op->rsc_id, op_type);
	}else {
		snprintf(proc_name, MAX_PROC_NAME, "%s:%s", rsc->id, op_type);
	}
	LRMAUDIT();
	return proc_name;
}
