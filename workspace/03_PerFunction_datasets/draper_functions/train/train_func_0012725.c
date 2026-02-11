alx_get_phy_info(struct alx_hw *hw)
{
	u16  devs1, devs2;

	if (alx_read_phy_reg(hw, MII_PHYSID1, &hw->phy_id[0]) ||
	    alx_read_phy_reg(hw, MII_PHYSID2, &hw->phy_id[1]))
		return false;


	if (alx_read_phy_ext(hw, 3, MDIO_DEVS1, &devs1) ||
	    alx_read_phy_ext(hw, 3, MDIO_DEVS2, &devs2))
		return false;
	hw->mdio.mmds = devs1 | devs2 << 16;

	return true;
}
