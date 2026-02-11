bfa_cee_get_attr(struct bfa_cee_s *cee, struct bfa_cee_attr_s *attr,
		 bfa_cee_get_attr_cbfn_t cbfn, void *cbarg)
{
	struct bfi_cee_get_req_s *cmd;

	WARN_ON((cee == NULL) || (cee->ioc == NULL));
	bfa_trc(cee, 0);
	if (!bfa_ioc_is_operational(cee->ioc)) {
		bfa_trc(cee, 0);
		return BFA_STATUS_IOC_FAILURE;
	}
	if (cee->get_attr_pending == BFA_TRUE) {
		bfa_trc(cee, 0);
		return  BFA_STATUS_DEVBUSY;
	}
	cee->get_attr_pending = BFA_TRUE;
	cmd = (struct bfi_cee_get_req_s *) cee->get_cfg_mb.msg;
	cee->attr = attr;
	cee->cbfn.get_attr_cbfn = cbfn;
	cee->cbfn.get_attr_cbarg = cbarg;
	bfi_h2i_set(cmd->mh, BFI_MC_CEE, BFI_CEE_H2I_GET_CFG_REQ,
		bfa_ioc_portid(cee->ioc));
	bfa_dma_be_addr_set(cmd->dma_addr, cee->attr_dma.pa);
	bfa_ioc_mbox_queue(cee->ioc, &cee->get_cfg_mb);

	return BFA_STATUS_OK;
}
