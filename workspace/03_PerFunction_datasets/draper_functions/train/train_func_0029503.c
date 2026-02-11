mdio_write(struct net_device *dev, int phy_id, int location,
		       int value)
{
	struct cp_private *cp = netdev_priv(dev);

	if (location == 0) {
		cpw8(Cfg9346, Cfg9346_Unlock);
		cpw16(BasicModeCtrl, value);
		cpw8(Cfg9346, Cfg9346_Lock);
	} else if (location < 8 && mii_2_8139_map[location])
		cpw16(mii_2_8139_map[location], value);
}
