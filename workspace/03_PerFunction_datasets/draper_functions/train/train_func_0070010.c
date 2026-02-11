map_mmioh_high(int min_pnode, int max_pnode)
{
	union uvh_rh_gam_mmioh_overlay_config_mmr_u mmioh;
	unsigned long mmr, base;
	int shift, enable, m_io, n_io;

	if (is_uv3_hub()) {

		map_mmioh_high_uv3(0, min_pnode, max_pnode);
		map_mmioh_high_uv3(1, min_pnode, max_pnode);
		return;
	}

	if (is_uv1_hub()) {
		mmr = UV1H_RH_GAM_MMIOH_OVERLAY_CONFIG_MMR;
		shift = UV1H_RH_GAM_MMIOH_OVERLAY_CONFIG_MMR_BASE_SHFT;
		mmioh.v = uv_read_local_mmr(mmr);
		enable = !!mmioh.s1.enable;
		base = mmioh.s1.base;
		m_io = mmioh.s1.m_io;
		n_io = mmioh.s1.n_io;
	} else if (is_uv2_hub()) {
		mmr = UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_MMR;
		shift = UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_MMR_BASE_SHFT;
		mmioh.v = uv_read_local_mmr(mmr);
		enable = !!mmioh.s2.enable;
		base = mmioh.s2.base;
		m_io = mmioh.s2.m_io;
		n_io = mmioh.s2.n_io;
	} else
		return;

	if (enable) {
		max_pnode &= (1 << n_io) - 1;
		pr_info(
		    "UV: base:0x%lx shift:%d N_IO:%d M_IO:%d max_pnode:0x%x\n",
			base, shift, m_io, n_io, max_pnode);
		map_high("MMIOH", base, shift, m_io, max_pnode, map_uc);
	} else {
		pr_info("UV: MMIOH disabled\n");
	}
}
