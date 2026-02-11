qed_int_igu_init_pure_rt(struct qed_hwfn *p_hwfn,
			      struct qed_ptt *p_ptt,
			      bool b_set,
			      bool b_slowpath)
{
	u32 igu_base_sb = p_hwfn->hw_info.p_igu_info->igu_base_sb;
	u32 igu_sb_cnt = p_hwfn->hw_info.p_igu_info->igu_sb_cnt;
	u32 sb_id = 0;
	u32 val = 0;

	val = qed_rd(p_hwfn, p_ptt, IGU_REG_BLOCK_CONFIGURATION);
	val |= IGU_REG_BLOCK_CONFIGURATION_VF_CLEANUP_EN;
	val &= ~IGU_REG_BLOCK_CONFIGURATION_PXP_TPH_INTERFACE_EN;
	qed_wr(p_hwfn, p_ptt, IGU_REG_BLOCK_CONFIGURATION, val);

	DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
		   "IGU cleaning SBs [%d,...,%d]\n",
		   igu_base_sb, igu_base_sb + igu_sb_cnt - 1);

	for (sb_id = igu_base_sb; sb_id < igu_base_sb + igu_sb_cnt; sb_id++)
		qed_int_igu_init_pure_rt_single(p_hwfn, p_ptt, sb_id,
						p_hwfn->hw_info.opaque_fid,
						b_set);

	if (b_slowpath) {
		sb_id = p_hwfn->hw_info.p_igu_info->igu_dsb_id;
		DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
			   "IGU cleaning slowpath SB [%d]\n", sb_id);
		qed_int_igu_init_pure_rt_single(p_hwfn, p_ptt, sb_id,
						p_hwfn->hw_info.opaque_fid,
						b_set);
	}
}
