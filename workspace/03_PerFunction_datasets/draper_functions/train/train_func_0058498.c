halt(struct sp_omsg *rq)
{
	struct  spptr  *cp;

	if  (rq->spr_jpslot >= Ptr_seg.dptr->ps_maxptrs)
		return;
	cp = &Ptr_seg.plist[rq->spr_jpslot].p;
#ifdef	NETWORK_VERSION
	if  (cp->spp_netid)  {
		ptr_message(cp, SO_PSTP);
		return;
	}
#endif

	switch  (cp->spp_state)  {
	case  SPP_INIT:
	case  SPP_RUN:
	case  SPP_SHUTD:
		cp->spp_sflags &= ~SPP_INTER;
		prabort(cp);
	case  SPP_WAIT:
	case  SPP_OPER:
		finp(cp);
		return;
	}
}
