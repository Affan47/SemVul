lli_init_bchan_out(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;

	FsmChangeState(fi, ST_WAIT_BCONN);
	if (chanp->debug & 1)
		link_debug(chanp, 0, "STAT_DCONN");
	HL_LL(chanp, ISDN_STAT_DCONN);
	init_b_st(chanp, 0);
	chanp->b_st->lli.l4l3(chanp->b_st, DL_ESTABLISH | REQUEST, NULL);
}
