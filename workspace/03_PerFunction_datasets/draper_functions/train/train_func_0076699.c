bnx2x_port_stats_base_init(struct bnx2x *bp)
{
	struct dmae_command *dmae;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);


	if (!bp->port.pmf || !bp->port.port_stx) {
		BNX2X_ERR("BUG!\n");
		return;
	}

	bp->executer_idx = 0;

	dmae = bnx2x_sp(bp, dmae[bp->executer_idx++]);
	dmae->opcode = bnx2x_dmae_opcode(bp, DMAE_SRC_PCI, DMAE_DST_GRC,
					 true, DMAE_COMP_PCI);
	dmae->src_addr_lo = U64_LO(bnx2x_sp_mapping(bp, port_stats));
	dmae->src_addr_hi = U64_HI(bnx2x_sp_mapping(bp, port_stats));
	dmae->dst_addr_lo = bp->port.port_stx >> 2;
	dmae->dst_addr_hi = 0;
	dmae->len = bnx2x_get_port_stats_dma_len(bp);
	dmae->comp_addr_lo = U64_LO(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_addr_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_val = DMAE_COMP_VAL;

	*stats_comp = 0;
	bnx2x_hw_stats_post(bp);
	bnx2x_stats_comp(bp);
}
