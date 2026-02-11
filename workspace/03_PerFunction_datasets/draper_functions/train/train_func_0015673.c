lrmd_op_new(void)
{
	lrmd_op_t* op = (lrmd_op_t*)calloc(sizeof(lrmd_op_t),1);

	if (op == NULL) {
		lrmd_log(LOG_ERR, "lrmd_op_new(): out of memory when "
			 "calloc a lrmd_op_t.");
		return NULL;
	}
	op->rsc_id = NULL;
	op->msg = NULL;
	op->exec_pid = -1;
	op->repeat_timeout_tag = 0;
	op->rapop = NULL;
	op->first_line_ra_stdout[0] = EOS;
	op->t_recv = time_longclock();
 	op->t_perform = zero_longclock;
 	op->t_done = zero_longclock;
 	op->t_rcchange = zero_longclock;
 	op->t_lastlogmsg = zero_longclock;

	memset(op->killseq, 0, sizeof(op->killseq));
	++lrm_objectstats.opcount;
	return op;
}
