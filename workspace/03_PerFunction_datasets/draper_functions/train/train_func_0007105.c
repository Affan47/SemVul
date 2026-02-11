wlc_phy_bist_check_phy(struct brcms_phy_pub *pih)
{
	struct brcms_phy *pi = container_of(pih, struct brcms_phy, pubpi_ro);
	u32 phybist0, phybist1, phybist2, phybist3, phybist4;

	if (NREV_GE(pi->pubpi.phy_rev, 16))
		return true;

	phybist0 = read_phy_reg(pi, 0x0e);
	phybist1 = read_phy_reg(pi, 0x0f);
	phybist2 = read_phy_reg(pi, 0xea);
	phybist3 = read_phy_reg(pi, 0xeb);
	phybist4 = read_phy_reg(pi, 0x156);

	if ((phybist0 == 0) && (phybist1 == 0x4000) && (phybist2 == 0x1fe0) &&
	    (phybist3 == 0) && (phybist4 == 0))
		return true;

	return false;
}
