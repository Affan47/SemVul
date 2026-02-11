mdio_read(struct net_device *dev, int phy_id, int location)
{
	int i;
	struct vortex_private *vp = netdev_priv(dev);
	int read_cmd = (0xf6 << 10) | (phy_id << 5) | location;
	unsigned int retval = 0;

	spin_lock_bh(&vp->mii_lock);

	if (mii_preamble_required)
		mdio_sync(vp, 32);


	for (i = 14; i >= 0; i--) {
		int dataval = (read_cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
		window_write16(vp, dataval, 4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
		window_write16(vp, dataval | MDIO_SHIFT_CLK,
			       4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
	}

	for (i = 19; i > 0; i--) {
		window_write16(vp, MDIO_ENB_IN, 4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
		retval = (retval << 1) |
			((window_read16(vp, 4, Wn4_PhysicalMgmt) &
			  MDIO_DATA_READ) ? 1 : 0);
		window_write16(vp, MDIO_ENB_IN | MDIO_SHIFT_CLK,
			       4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
	}

	spin_unlock_bh(&vp->mii_lock);

	return retval & 0x20000 ? 0xffff : retval>>1 & 0xffff;
}
