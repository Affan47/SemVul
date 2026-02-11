qed_hw_init_pf(struct qed_hwfn *p_hwfn,
			  struct qed_ptt *p_ptt,
			  int hw_mode,
			  bool b_hw_start,
			  enum qed_int_mode int_mode,
			  bool allow_npar_tx_switch)
{
	u8 rel_pf_id = p_hwfn->rel_pf_id;
	int rc = 0;

	if (p_hwfn->mcp_info) {
		struct qed_mcp_function_info *p_info;

		p_info = &p_hwfn->mcp_info->func_info;
		if (p_info->bandwidth_min)
			p_hwfn->qm_info.pf_wfq = p_info->bandwidth_min;


		p_hwfn->qm_info.pf_rl = 100;
	}

	qed_cxt_hw_init_pf(p_hwfn);

	qed_int_igu_init_rt(p_hwfn);


	if (hw_mode & (1 << MODE_MF_SD)) {
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW, "Configuring LLH_FUNC_TAG\n");
		STORE_RT_REG(p_hwfn, NIG_REG_LLH_FUNC_TAG_EN_RT_OFFSET, 1);
		STORE_RT_REG(p_hwfn, NIG_REG_LLH_FUNC_TAG_VALUE_RT_OFFSET,
			     p_hwfn->hw_info.ovlan);
	}


	if (hw_mode & (1 << MODE_MF_SI)) {
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "Configuring TAGMAC_CLS_TYPE\n");
		STORE_RT_REG(p_hwfn,
			     NIG_REG_LLH_FUNC_TAGMAC_CLS_TYPE_RT_OFFSET, 1);
	}


	STORE_RT_REG(p_hwfn, PRS_REG_SEARCH_TCP_RT_OFFSET, 0);
	STORE_RT_REG(p_hwfn, PRS_REG_SEARCH_FCOE_RT_OFFSET, 0);
	STORE_RT_REG(p_hwfn, PRS_REG_SEARCH_ROCE_RT_OFFSET, 0);


	rc = qed_final_cleanup(p_hwfn, p_ptt, rel_pf_id);
	if (rc != 0)
		return rc;


	rc = qed_init_run(p_hwfn, p_ptt, PHASE_PF, rel_pf_id, hw_mode);
	if (rc)
		return rc;


	rc = qed_init_run(p_hwfn, p_ptt, PHASE_QM_PF, rel_pf_id, hw_mode);
	if (rc)
		return rc;


	qed_int_igu_init_pure_rt(p_hwfn, p_ptt, true, true);

	if (b_hw_start) {

		qed_int_igu_enable(p_hwfn, p_ptt, int_mode);


		rc = qed_sp_pf_start(p_hwfn, p_hwfn->cdev->mf_mode);
		if (rc)
			DP_NOTICE(p_hwfn, "Function start ramrod failed\n");
	}
	return rc;
}
