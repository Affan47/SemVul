wlc_lcnphy_rx_gain_override_enable(struct brcms_phy *pi, bool enable)
{
	u16 ebit = enable ? 1 : 0;

	mod_phy_reg(pi, 0x4b0, (0x1 << 8), ebit << 8);

	mod_phy_reg(pi, 0x44c, (0x1 << 0), ebit << 0);

	if (LCNREV_LT(pi->pubpi.phy_rev, 2)) {
		mod_phy_reg(pi, 0x44c, (0x1 << 4), ebit << 4);
		mod_phy_reg(pi, 0x44c, (0x1 << 6), ebit << 6);
		mod_phy_reg(pi, 0x4b0, (0x1 << 5), ebit << 5);
		mod_phy_reg(pi, 0x4b0, (0x1 << 6), ebit << 6);
	} else {
		mod_phy_reg(pi, 0x4b0, (0x1 << 12), ebit << 12);
		mod_phy_reg(pi, 0x4b0, (0x1 << 13), ebit << 13);
		mod_phy_reg(pi, 0x4b0, (0x1 << 5), ebit << 5);
	}

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		mod_phy_reg(pi, 0x4b0, (0x1 << 10), ebit << 10);
		mod_phy_reg(pi, 0x4e5, (0x1 << 3), ebit << 3);
	}
}
