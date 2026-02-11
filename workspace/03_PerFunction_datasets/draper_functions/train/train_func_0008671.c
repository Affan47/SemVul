proper(struct sp_cmsg *rq)
{
	Hashspptr	*hcp;
	struct  spptr  *cp;

	if  (rq->spr_pslot >= Ptr_seg.dptr->ps_maxptrs)
		return;

	hcp = &Ptr_seg.plist[rq->spr_pslot];
	cp = &hcp->p;


	if  (cp->spp_sflags & SPP_HEOJ)  {
		finp(cp);
		return;
	}

	if  (cp->spp_state < SPP_PROC)
		return;


	if  (cp->spp_state == SPP_OPER)  {
		Hashspq		*hjj = &Job_seg.jlist[cp->spp_jslot];
		struct	spq	*jj = &hjj->j;
		if  (cp->spp_jslot < 0  ||  jj->spq_job != cp->spp_job)  {
			nowaiting(cp);
			Ptr_seg.Last_ser++;
			qchanges++;
			Ptr_seg.dptr->ps_serial++;
#ifdef	NETWORK_VERSION
			if  ((cp->spp_netflags & SPP_LOCALONLY) == 0)
				ptr_broadcast(hcp, SP_CHANGEDPTR);
#endif
			return;
		}

		if  (jj->spq_jflags & (SPQ_MATTN|SPQ_WATTN))
			notify(jj, cp, 53, (jobno_t) 0, PRESENT_TENSE);
	}

	Ptr_seg.Last_ser++;
	qchanges++;
	Ptr_seg.dptr->ps_serial++;
#ifdef	NETWORK_VERSION
	if  ((cp->spp_netflags & SPP_LOCALONLY) == 0)
		ptr_broadcast(hcp, SP_CHANGEDPTR);
#endif
}
