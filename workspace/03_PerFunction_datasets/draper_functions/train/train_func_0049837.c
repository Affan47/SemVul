find_pslot(const netid_t hostid, const slotno_t slotn)
{
	LONG  pind;

	PTRS_LOCK;
	check_pmoved();
	pind = Ptr_seg.hashp_pid[pid_hash(hostid, slotn)];
	while  (pind >= 0L)  {
		Hashspptr  *hcp = &Ptr_seg.plist[pind];
		struct  spptr	*cp = &hcp->p;
		if  (cp->spp_state != SPP_NULL  &&  cp->spp_netid == hostid  &&  cp->spp_rslot == slotn)  {
			PTRS_UNLOCK;
			return  (slotno_t) pind;
		}
		pind = hcp->nxt_pid_hash;
	}
	PTRS_UNLOCK;
	disp_str = look_host(hostid);
	disp_arg[1] = slotn;
	nfreport(1136);
	return  -1;
}
