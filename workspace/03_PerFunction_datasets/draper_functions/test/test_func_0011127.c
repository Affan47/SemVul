wlc_lcnphy_rfseq_tbl_adc_pwrup(struct brcms_phy *pi)
{
	u16 N1, N2, N3, N4, N5, N6, N;
	N1 = ((read_phy_reg(pi, 0x4a5) & (0xff << 0))
	      >> 0);
	N2 = 1 << ((read_phy_reg(pi, 0x4a5) & (0x7 << 12))
		   >> 12);
	N3 = ((read_phy_reg(pi, 0x40d) & (0xff << 0))
	      >> 0);
	N4 = 1 << ((read_phy_reg(pi, 0x40d) & (0x7 << 8))
		   >> 8);
	N5 = ((read_phy_reg(pi, 0x4a2) & (0xff << 0))
	      >> 0);
	N6 = 1 << ((read_phy_reg(pi, 0x4a2) & (0x7 << 8))
		   >> 8);
	N = 2 * (N1 + N2 + N3 + N4 + 2 * (N5 + N6)) + 80;
	if (N < 1600)
		N = 1600;
	return N;
}
