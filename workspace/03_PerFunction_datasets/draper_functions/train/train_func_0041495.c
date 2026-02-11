alx_mdio_write(struct net_device *netdev,
			  int prtad, int devad, u16 addr, u16 val)
{
	struct alx_priv *alx = netdev_priv(netdev);
	struct alx_hw *hw = &alx->hw;

	if (prtad != hw->mdio.prtad)
		return -EINVAL;

	if (devad == MDIO_DEVAD_NONE)
		return alx_write_phy_reg(hw, addr, val);

	return alx_write_phy_ext(hw, devad, addr, val);
}
