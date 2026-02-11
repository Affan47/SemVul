lli_leased_in(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;
	isdn_ctrl ic;
	int ret;

	if (!chanp->leased)
		return;
	chanp->cs->cardmsg(chanp->cs, MDL_INFO_SETUP, (void *) (long)chanp->chan);
	FsmChangeState(fi, ST_IN_WAIT_LL);
	if (chanp->debug & 1)
		link_debug(chanp, 0, "STAT_ICALL_LEASED");
	ic.driver = chanp->cs->myid;
	ic.command = ((chanp->chan < 2) ? ISDN_STAT_ICALL : ISDN_STAT_ICALLW);
	ic.arg = chanp->chan;
	ic.parm.setup.si1 = 7;
	ic.parm.setup.si2 = 0;
	ic.parm.setup.plan = 0;
	ic.parm.setup.screen = 0;
	sprintf(ic.parm.setup.eazmsn, "%d", chanp->chan + 1);
	sprintf(ic.parm.setup.phone, "LEASED%d", chanp->cs->myid);
	ret = chanp->cs->iif.statcallb(&ic);
	if (chanp->debug & 1)
		link_debug(chanp, 1, "statcallb ret=%d", ret);
	if (!ret) {
		chanp->cs->cardmsg(chanp->cs, MDL_INFO_REL, (void *) (long)chanp->chan);
		FsmChangeState(fi, ST_NULL);
	}
}
