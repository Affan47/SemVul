bnx2_init_copper_phy(struct bnx2 *bp)
{
	u32 val;

	bp->phy_flags |= PHY_CRC_FIX_FLAG;

	if (bp->phy_flags & PHY_CRC_FIX_FLAG) {
		bnx2_write_phy(bp, 0x18, 0x0c00);
		bnx2_write_phy(bp, 0x17, 0x000a);
		bnx2_write_phy(bp, 0x15, 0x310b);
		bnx2_write_phy(bp, 0x17, 0x201f);
		bnx2_write_phy(bp, 0x15, 0x9506);
		bnx2_write_phy(bp, 0x17, 0x401f);
		bnx2_write_phy(bp, 0x15, 0x14e2);
		bnx2_write_phy(bp, 0x18, 0x0400);
	}

	bnx2_write_phy(bp, 0x18, 0x7);
	bnx2_read_phy(bp, 0x18, &val);
	bnx2_write_phy(bp, 0x18, val & ~0x4007);

	bnx2_read_phy(bp, 0x10, &val);
	bnx2_write_phy(bp, 0x10, val & ~0x1);


	bnx2_write_phy(bp, 0x18, 0x7007);
	bnx2_read_phy(bp, 0x18, &val);
	bnx2_write_phy(bp, 0x18, val | (1 << 15) | (1 << 4));
	return 0;
}
