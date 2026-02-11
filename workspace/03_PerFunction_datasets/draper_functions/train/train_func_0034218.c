lcp_close(unit)
    int unit;
{
    fsm *f = &lcp_fsm[unit];

    if (f->state == STOPPED && f->flags & (OPT_PASSIVE|OPT_SILENT)) {


	f->state = CLOSED;
	lcp_finished(f);

    } else
	fsm_close(&lcp_fsm[unit]);
}
