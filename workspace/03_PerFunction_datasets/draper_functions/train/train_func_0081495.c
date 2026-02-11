lcp_close(int unit,char *reason)
{
    fsm *f = &lcp_fsm[unit];

	if(unit < 0) {
		syslog(LOG_ERR, "lcp_closed called with unit < 0");
		return;
	}

    if (f->state == STOPPED && f->flags & (OPT_PASSIVE|OPT_SILENT)) {


	f->state = CLOSED;
	lcp_finished(f);

    } else
	fsm_close(&lcp_fsm[unit],reason);
}
