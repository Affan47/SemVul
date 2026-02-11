assign(Hashspq *hjp, Hashspptr *hpp)
{
	struct	spq	*jp = &hjp->j;
	struct	spptr	*pp = &hpp->p;

#ifdef	SHED_FORMASSIGN


	strncpy(pp->spp_form, jp->spq_form, sizeof(jp->spq_form));
#endif


	jp->spq_sflags |= SPQ_ASSIGN;
	jp->spq_pslot = hpp - Ptr_seg.plist;
	pp->spp_job = jp->spq_job;
	pp->spp_rjhostid = jp->spq_netid;
	pp->spp_rjslot = jp->spq_rslot;


	Ptr_seg.dptr->ps_serial++;
	Job_seg.dptr->js_serial++;
	Job_seg.Last_ser++;
	qchanges++;

#ifdef	NETWORK_VERSION
	if  (jp->spq_netid)  {
		pp->spp_sflags = SPP_SELECT | SPP_PROPOSED;
		jp->spq_sflags |= SPQ_PROPOSED;
		job_message(jp->spq_netid, jp, SO_PROPOSE, (ULONG) (hjp - Job_seg.jlist), (ULONG) (hpp - Ptr_seg.plist));
	}
	else  {
#endif
		pp->spp_jslot = hjp - Job_seg.jlist;
#ifdef	NETWORK_VERSION
		if  (!(jp->spq_jflags & SPQ_LOCALONLY))  {
			if  (pp->spp_netflags & SPP_LOCALONLY)
				job_broadcast(hjp, SO_LOCASSIGN);
			else
				ptr_assxmit(hjp, hpp);
		}
#endif
		startj(hjp, pp);
#ifdef	NETWORK_VERSION
	}
#endif
}
