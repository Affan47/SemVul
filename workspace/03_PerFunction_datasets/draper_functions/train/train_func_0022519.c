bfa_faa_query(struct bfa_s *bfa, struct bfa_faa_attr_s *attr,
		bfa_cb_iocfc_t cbfn, void *cbarg)
{
	struct bfi_faa_query_s  faa_attr_req;
	struct bfa_iocfc_s      *iocfc = &bfa->iocfc;
	bfa_status_t            status;

	status = bfa_faa_validate_request(bfa);
	if (status != BFA_STATUS_OK)
		return status;

	if (iocfc->faa_args.busy == BFA_TRUE)
		return BFA_STATUS_DEVBUSY;

	iocfc->faa_args.faa_attr = attr;
	iocfc->faa_args.faa_cb.faa_cbfn = cbfn;
	iocfc->faa_args.faa_cb.faa_cbarg = cbarg;

	iocfc->faa_args.busy = BFA_TRUE;
	memset(&faa_attr_req, 0, sizeof(struct bfi_faa_query_s));
	bfi_h2i_set(faa_attr_req.mh, BFI_MC_IOCFC,
		BFI_IOCFC_H2I_FAA_QUERY_REQ, bfa_fn_lpu(bfa));

	bfa_ioc_mbox_send(&bfa->ioc, &faa_attr_req,
		sizeof(struct bfi_faa_query_s));

	return BFA_STATUS_OK;
}
