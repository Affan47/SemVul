bfa_rport_create(struct bfa_s *bfa, void *rport_drv)
{
	struct bfa_rport_s *rp;

	rp = bfa_rport_alloc(BFA_RPORT_MOD(bfa));

	if (rp == NULL)
		return NULL;

	rp->bfa = bfa;
	rp->rport_drv = rport_drv;
	memset(&rp->stats, 0, sizeof(rp->stats));

	WARN_ON(!bfa_sm_cmp_state(rp, bfa_rport_sm_uninit));
	bfa_sm_send_event(rp, BFA_RPORT_SM_CREATE);

	return rp;
}
