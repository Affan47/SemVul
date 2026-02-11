qed_int_igu_enable(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt,
		       enum qed_int_mode int_mode)
{
	int rc, i;


	for (i = 0; i < 9; i++)
		qed_wr(p_hwfn, p_ptt,
		       MISC_REG_AEU_ENABLE1_IGU_OUT_0 + (i << 2), 0);


	qed_wr(p_hwfn, p_ptt, IGU_REG_LEADING_EDGE_LATCH, 0xfff);
	qed_wr(p_hwfn, p_ptt, IGU_REG_TRAILING_EDGE_LATCH, 0xfff);


	mmiowb();


	qed_wr(p_hwfn, p_ptt, MISC_REG_AEU_MASK_ATTN_IGU, 0xff);
	if ((int_mode != QED_INT_MODE_INTA) || IS_LEAD_HWFN(p_hwfn)) {
		rc = qed_slowpath_irq_req(p_hwfn);
		if (rc != 0) {
			DP_NOTICE(p_hwfn, "Slowpath IRQ request failed\n");
			return -EINVAL;
		}
		p_hwfn->b_int_requested = true;
	}

	qed_int_igu_enable_int(p_hwfn, p_ptt, int_mode);
	p_hwfn->b_int_enabled = 1;

	return rc;
}
