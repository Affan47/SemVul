bfa_fcs_fabric_attach(struct bfa_fcs_s *fcs)
{
	struct bfa_fcs_fabric_s *fabric;

	fabric = &fcs->fabric;
	memset(fabric, 0, sizeof(struct bfa_fcs_fabric_s));


	fabric->fcs = fcs;
	INIT_LIST_HEAD(&fabric->vport_q);
	INIT_LIST_HEAD(&fabric->vf_q);
	fabric->lps = bfa_lps_alloc(fcs->bfa);
	WARN_ON(!fabric->lps);


	bfa_wc_init(&fabric->wc, bfa_fcs_fabric_delete_comp, fabric);
	bfa_wc_up(&fabric->wc);

	bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_uninit);
	bfa_fcs_lport_attach(&fabric->bport, fabric->fcs, FC_VF_ID_NULL, NULL);
}
