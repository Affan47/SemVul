map_gru_distributed(unsigned long c)
{
	union uvh_rh_gam_gru_overlay_config_mmr_u gru;
	u64 paddr;
	unsigned long bytes;
	int nid;

	gru.v = c;

	gru_dist_base = gru.v & 0x000007fff0000000UL;
	if (!gru_dist_base) {
		pr_info("UV: Map GRU_DIST base address NULL\n");
		return;
	}
	bytes = 1UL << UVH_RH_GAM_GRU_OVERLAY_CONFIG_MMR_BASE_SHFT;
	gru_dist_lmask = ((1UL << uv_hub_info->m_val) - 1) & ~(bytes - 1);
	gru_dist_umask = ~((1UL << uv_hub_info->m_val) - 1);
	gru_dist_base &= gru_dist_lmask;
	for_each_online_node(nid) {
		paddr = ((u64)uv_node_to_pnode(nid) << uv_hub_info->m_val) |
				gru_dist_base;
		init_extra_mapping_wb(paddr, bytes);
		gru_first_node_paddr = min(paddr, gru_first_node_paddr);
		gru_last_node_paddr = max(paddr, gru_last_node_paddr);
	}

	gru_first_node_paddr &= gru_dist_umask;
	gru_last_node_paddr &= gru_dist_umask;
	pr_debug("UV: Map GRU_DIST base 0x%016llx  0x%016llx - 0x%016llx\n",
		gru_dist_base, gru_first_node_paddr, gru_last_node_paddr);
}
