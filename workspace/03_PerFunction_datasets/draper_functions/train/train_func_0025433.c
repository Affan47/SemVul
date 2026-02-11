delptr(struct sp_omsg *rq)
{
	Hashspptr  *hcp;
	struct  spptr  *cp;

	if  (rq->spr_jpslot >= Ptr_seg.dptr->ps_maxptrs)
		return;
	hcp = &Ptr_seg.plist[rq->spr_jpslot];
	cp = &hcp->p;
	if  (cp->spp_state == SPP_NULL || cp->spp_pid != 0)
		return;
#ifdef	NETWORK_VERSION
	if  (cp->spp_netid)  {
		if  (rq->spr_netid == 0)  {
			ptr_message(cp, SO_DELP);
			return;
		}
	}
	else  if  ((cp->spp_netflags & SPP_LOCALONLY) == 0)
		ptr_broadcast(hcp, SO_DELP);
#endif
	ptrs_lock();
	Ptr_seg.dptr->ps_serial++;
	takeoff_l(rq->spr_jpslot);
	ptrs_unlock();
	Ptr_seg.Last_ser++;
	qchanges++;
}
