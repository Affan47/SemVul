bfa_ablk_pf_update(struct bfa_ablk_s *ablk, int pcifn, u16 bw_min,
		   u16 bw_max, bfa_ablk_cbfn_t cbfn, void *cbarg)
{
	struct bfi_ablk_h2i_pf_req_s *m;

	if (!bfa_ioc_is_operational(ablk->ioc)) {
		bfa_trc(ablk->ioc, BFA_STATUS_IOC_FAILURE);
		return BFA_STATUS_IOC_FAILURE;
	}

	if (ablk->busy) {
		bfa_trc(ablk->ioc, BFA_STATUS_DEVBUSY);
		return  BFA_STATUS_DEVBUSY;
	}

	ablk->cbfn  = cbfn;
	ablk->cbarg = cbarg;
	ablk->busy  = BFA_TRUE;

	m = (struct bfi_ablk_h2i_pf_req_s *)ablk->mb.msg;
	bfi_h2i_set(m->mh, BFI_MC_ABLK, BFI_ABLK_H2I_PF_UPDATE,
		bfa_ioc_portid(ablk->ioc));
	m->pcifn = (u8)pcifn;
	m->bw_min = cpu_to_be16(bw_min);
	m->bw_max = cpu_to_be16(bw_max);
	bfa_ioc_mbox_queue(ablk->ioc, &ablk->mb);

	return BFA_STATUS_OK;
}
