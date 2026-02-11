qed_gtt_init(struct qed_hwfn *p_hwfn)
{
	u32 gtt_base;
	u32 i;


	gtt_base = PXP_PF_WINDOW_ADMIN_START + PXP_PF_WINDOW_ADMIN_GLOBAL_START;

	for (i = 0; i < ARRAY_SIZE(pxp_global_win); i++)
		if (pxp_global_win[i])
			REG_WR(p_hwfn, gtt_base + i * PXP_GLOBAL_ENTRY_SIZE,
			       pxp_global_win[i]);
}
