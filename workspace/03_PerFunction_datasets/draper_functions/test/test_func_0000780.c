cnt_wait(struct sess *sp)
{
	int i;
	struct pollfd pfd[1];
	struct worker *wrk;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	wrk = sp->wrk;
	CHECK_OBJ_NOTNULL(wrk, WORKER_MAGIC);
	AZ(sp->vcl);
	AZ(wrk->obj);
	AZ(sp->esi_level);
	assert(sp->xid == 0);

	i = HTC_Complete(sp->htc);
	if (i == 0 && cache_param->session_linger > 0) {
		pfd[0].fd = sp->fd;
		pfd[0].events = POLLIN;
		pfd[0].revents = 0;
		i = poll(pfd, 1, cache_param->session_linger);
		if (i)
			i = HTC_Rx(sp->htc);
	}
	if (i == 0) {
		WSP(sp, SLT_Debug, "herding");
		wrk->stats.sess_herd++;
		SES_Charge(sp);
		Pool_Wait(sp);
		return (1);
	}
	if (i == 1) {
		sp->step = STP_START;
		return (0);
	}
	if (i == -2) {
		SES_Close(sp, "overflow");
	} else if (i == -1 && Tlen(sp->htc->rxbuf) == 0 &&
	    (errno == 0 || errno == ECONNRESET))
		SES_Close(sp, "EOF");
	else
		SES_Close(sp, "error");
	sp->step = STP_DONE;
	return (0);
}
