restart(struct sp_omsg *rq)
{
	struct  spptr  *cp;
	if  (rq->spr_jpslot >= Ptr_seg.dptr->ps_maxptrs)
		return;
	cp = &Ptr_seg.plist[rq->spr_jpslot].p;
#ifdef	NETWORK_VERSION
	if  (cp->spp_netid)
		ptr_message(cp, SO_RSP);
	else  if  (cp->spp_state == SPP_RUN)
#endif
		kill((PIDTYPE) cp->spp_pid, DAEMRST);
}
