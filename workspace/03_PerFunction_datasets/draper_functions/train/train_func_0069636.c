prjab(struct sp_omsg *rq)
{
	Hashspptr	*hcp;
	struct  spptr  *cp;

	if  (rq->spr_jpslot >= Ptr_seg.dptr->ps_maxptrs)
		return;

	hcp = &Ptr_seg.plist[rq->spr_jpslot];
	cp = &hcp->p;

#ifdef	NETWORK_VERSION
	if  (cp->spp_netid)
		ptr_message(cp, SO_PJAB);
	else  {
#endif
		if  (cp->spp_jslot >= 0  &&  cp->spp_jslot < Job_seg.dptr->js_maxjobs)
			Job_seg.jlist[cp->spp_jslot].j.spq_sflags |= SPQ_ABORTJ;

		if  (cp->spp_state >= SPP_PROC)  {
			cp->spp_sflags &= SPP_HEOJ;
			Ptr_seg.dptr->ps_serial++;
			if  (cp->spp_state == SPP_OPER)
				nowaiting(cp);
			else  if  (cp->spp_state == SPP_RUN)
				prabort(cp);
			if  (cp->spp_state != SPP_SHUTD  &&  cp->spp_sflags & SPP_HEOJ)
				finp(cp);
		}
#ifdef	NETWORK_VERSION
	}
#endif
}
