bnx2_set_rx_mode(struct nic *nic __unused)
{
	struct bnx2 *bp = &bnx2;
	u32 rx_mode, sort_mode;
	int i;

	rx_mode = bp->rx_mode & ~(BNX2_EMAC_RX_MODE_PROMISCUOUS |
				  BNX2_EMAC_RX_MODE_KEEP_VLAN_TAG);
	sort_mode = 1 | BNX2_RPM_SORT_USER0_BC_EN;

	if (!(bp->flags & ASF_ENABLE_FLAG)) {
		rx_mode |= BNX2_EMAC_RX_MODE_KEEP_VLAN_TAG;
	}


	for (i = 0; i < NUM_MC_HASH_REGISTERS; i++) {
		REG_WR(bp, BNX2_EMAC_MULTICAST_HASH0 + (i * 4),
		       0xffffffff);
       	}
	sort_mode |= BNX2_RPM_SORT_USER0_MC_EN;

	if (rx_mode != bp->rx_mode) {
		bp->rx_mode = rx_mode;
		REG_WR(bp, BNX2_EMAC_RX_MODE, rx_mode);
	}

	REG_WR(bp, BNX2_RPM_SORT_USER0, 0x0);
	REG_WR(bp, BNX2_RPM_SORT_USER0, sort_mode);
	REG_WR(bp, BNX2_RPM_SORT_USER0, sort_mode | BNX2_RPM_SORT_USER0_ENA);
}
