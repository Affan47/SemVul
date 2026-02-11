claim_fcxps_mem(struct bfa_fcxp_mod_s *mod)
{
	u16	i;
	struct bfa_fcxp_s *fcxp;

	fcxp = (struct bfa_fcxp_s *) bfa_mem_kva_curp(mod);
	memset(fcxp, 0, sizeof(struct bfa_fcxp_s) * mod->num_fcxps);

	INIT_LIST_HEAD(&mod->fcxp_req_free_q);
	INIT_LIST_HEAD(&mod->fcxp_rsp_free_q);
	INIT_LIST_HEAD(&mod->fcxp_active_q);
	INIT_LIST_HEAD(&mod->fcxp_req_unused_q);
	INIT_LIST_HEAD(&mod->fcxp_rsp_unused_q);

	mod->fcxp_list = fcxp;

	for (i = 0; i < mod->num_fcxps; i++) {
		fcxp->fcxp_mod = mod;
		fcxp->fcxp_tag = i;

		if (i < (mod->num_fcxps / 2)) {
			list_add_tail(&fcxp->qe, &mod->fcxp_req_free_q);
			fcxp->req_rsp = BFA_TRUE;
		} else {
			list_add_tail(&fcxp->qe, &mod->fcxp_rsp_free_q);
			fcxp->req_rsp = BFA_FALSE;
		}

		bfa_reqq_winit(&fcxp->reqq_wqe, bfa_fcxp_qresume, fcxp);
		fcxp->reqq_waiting = BFA_FALSE;

		fcxp = fcxp + 1;
	}

	bfa_mem_kva_curp(mod) = (void *)fcxp;
}
