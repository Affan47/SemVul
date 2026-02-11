qed_hw_reset(struct qed_dev *cdev)
{
	int rc = 0;
	u32 unload_resp, unload_param;
	int i;

	for_each_hwfn(cdev, i) {
		struct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		DP_VERBOSE(p_hwfn, NETIF_MSG_IFDOWN, "Resetting hw/fw\n");


		qed_reg_assert(p_hwfn, p_hwfn->p_main_ptt,
			       QM_REG_USG_CNT_PF_TX, 0);
		qed_reg_assert(p_hwfn, p_hwfn->p_main_ptt,
			       QM_REG_USG_CNT_PF_OTHER, 0);


		qed_wr(p_hwfn, p_hwfn->p_main_ptt, DORQ_REG_PF_DB_ENABLE, 0);
		qed_wr(p_hwfn, p_hwfn->p_main_ptt, QM_REG_PF_EN, 0);
		qed_wr(p_hwfn, p_hwfn->p_main_ptt,
		       TCFC_REG_STRONG_ENABLE_PF, 0);
		qed_wr(p_hwfn, p_hwfn->p_main_ptt,
		       CCFC_REG_STRONG_ENABLE_PF, 0);


		rc = qed_mcp_cmd(p_hwfn, p_hwfn->p_main_ptt,
				 DRV_MSG_CODE_UNLOAD_REQ,
				 DRV_MB_PARAM_UNLOAD_WOL_MCP,
				 &unload_resp, &unload_param);
		if (rc) {
			DP_NOTICE(p_hwfn, "qed_hw_reset: UNLOAD_REQ failed\n");
			unload_resp = FW_MSG_CODE_DRV_UNLOAD_ENGINE;
		}

		rc = qed_mcp_cmd(p_hwfn, p_hwfn->p_main_ptt,
				 DRV_MSG_CODE_UNLOAD_DONE,
				 0, &unload_resp, &unload_param);
		if (rc) {
			DP_NOTICE(p_hwfn, "qed_hw_reset: UNLOAD_DONE failed\n");
			return rc;
		}
	}

	return rc;
}
