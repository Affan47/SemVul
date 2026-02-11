lcp_close(unit, reason)
    int unit;
    char *reason;
{
    fsm *f = &lcp_fsm[unit];

    if (phase != PHASE_DEAD && phase != PHASE_MASTER)
	new_phase(PHASE_TERMINATE);
    if (f->state == STOPPED && f->flags & (OPT_PASSIVE|OPT_SILENT)) {


	f->state = CLOSED;
	lcp_finished(f);

    } else
	fsm_close(f, reason);
}
