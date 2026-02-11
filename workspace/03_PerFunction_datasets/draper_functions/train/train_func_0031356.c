bfa_fcxp_res_recfg(struct bfa_s *bfa, u16 num_fcxp_fw)
{
	struct bfa_fcxp_mod_s	*mod = BFA_FCXP_MOD(bfa);
	struct list_head	*qe;
	int	i;

	for (i = 0; i < (mod->num_fcxps - num_fcxp_fw); i++) {
		if (i < ((mod->num_fcxps - num_fcxp_fw) / 2)) {
			bfa_q_deq_tail(&mod->fcxp_req_free_q, &qe);
			list_add_tail(qe, &mod->fcxp_req_unused_q);
		} else {
			bfa_q_deq_tail(&mod->fcxp_rsp_free_q, &qe);
			list_add_tail(qe, &mod->fcxp_rsp_unused_q);
		}
	}
}
