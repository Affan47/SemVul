bnx2x_stats_init(struct bnx2x *bp)
{
	int port = BP_PORT(bp);
	int mb_idx = BP_FW_MB_IDX(bp);

	if (IS_VF(bp)) {
		bnx2x_memset_stats(bp);
		return;
	}

	bp->stats_pending = 0;
	bp->executer_idx = 0;
	bp->stats_counter = 0;


	if (!BP_NOMCP(bp)) {
		bp->port.port_stx = SHMEM_RD(bp, port_mb[port].port_stx);
		bp->func_stx = SHMEM_RD(bp, func_mb[mb_idx].fw_mb_param);

	} else {
		bp->port.port_stx = 0;
		bp->func_stx = 0;
	}
	DP(BNX2X_MSG_STATS, "port_stx 0x%x  func_stx 0x%x\n",
	   bp->port.port_stx, bp->func_stx);


	if (!bp->stats_init && bp->port.pmf && bp->port.port_stx)
		bnx2x_stats_handle(bp, STATS_EVENT_PMF);

	port = BP_PORT(bp);

	memset(&(bp->port.old_nig_stats), 0, sizeof(struct nig_stats));
	bp->port.old_nig_stats.brb_discard =
			REG_RD(bp, NIG_REG_STAT0_BRB_DISCARD + port*0x38);
	bp->port.old_nig_stats.brb_truncate =
			REG_RD(bp, NIG_REG_STAT0_BRB_TRUNCATE + port*0x38);
	if (!CHIP_IS_E3(bp)) {
		REG_RD_DMAE(bp, NIG_REG_STAT0_EGRESS_MAC_PKT0 + port*0x50,
			    &(bp->port.old_nig_stats.egress_mac_pkt0_lo), 2);
		REG_RD_DMAE(bp, NIG_REG_STAT0_EGRESS_MAC_PKT1 + port*0x50,
			    &(bp->port.old_nig_stats.egress_mac_pkt1_lo), 2);
	}


	bnx2x_prep_fw_stats_req(bp);


	if (bp->stats_init) {
		if (bp->func_stx) {
			memset(bnx2x_sp(bp, func_stats), 0,
			       sizeof(struct host_func_stats));
			bnx2x_func_stats_init(bp);
			bnx2x_hw_stats_post(bp);
			bnx2x_stats_comp(bp);
		}
	}

	bnx2x_memset_stats(bp);
}
