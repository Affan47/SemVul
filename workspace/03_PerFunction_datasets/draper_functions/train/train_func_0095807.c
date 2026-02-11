bnx2_init_copper_phy(struct bnx2 *bp, int reset_phy)
{
	u32 val;

	if (reset_phy)
		bnx2_reset_phy(bp);

	if (bp->phy_flags & BNX2_PHY_FLAG_CRC_FIX) {
		bnx2_write_phy(bp, 0x18, 0x0c00);
		bnx2_write_phy(bp, 0x17, 0x000a);
		bnx2_write_phy(bp, 0x15, 0x310b);
		bnx2_write_phy(bp, 0x17, 0x201f);
		bnx2_write_phy(bp, 0x15, 0x9506);
		bnx2_write_phy(bp, 0x17, 0x401f);
		bnx2_write_phy(bp, 0x15, 0x14e2);
		bnx2_write_phy(bp, 0x18, 0x0400);
	}

	if (bp->phy_flags & BNX2_PHY_FLAG_DIS_EARLY_DAC) {
		bnx2_write_phy(bp, MII_BNX2_DSP_ADDRESS,
			       MII_BNX2_DSP_EXPAND_REG | 0x8);
		bnx2_read_phy(bp, MII_BNX2_DSP_RW_PORT, &val);
		val &= ~(1 << 8);
		bnx2_write_phy(bp, MII_BNX2_DSP_RW_PORT, val);
	}

	if (bp->dev->mtu > 1500) {

		bnx2_write_phy(bp, 0x18, 0x7);
		bnx2_read_phy(bp, 0x18, &val);
		bnx2_write_phy(bp, 0x18, val | 0x4000);

		bnx2_read_phy(bp, 0x10, &val);
		bnx2_write_phy(bp, 0x10, val | 0x1);
	}
	else {
		bnx2_write_phy(bp, 0x18, 0x7);
		bnx2_read_phy(bp, 0x18, &val);
		bnx2_write_phy(bp, 0x18, val & ~0x4007);

		bnx2_read_phy(bp, 0x10, &val);
		bnx2_write_phy(bp, 0x10, val & ~0x1);
	}


	bnx2_write_phy(bp, MII_BNX2_AUX_CTL, AUX_CTL_MISC_CTL);
	bnx2_read_phy(bp, MII_BNX2_AUX_CTL, &val);
	val |=  AUX_CTL_MISC_CTL_WR | AUX_CTL_MISC_CTL_WIRESPEED;


	if (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		val |=  AUX_CTL_MISC_CTL_AUTOMDIX;

	bnx2_write_phy(bp, MII_BNX2_AUX_CTL, val);
	return 0;
}
