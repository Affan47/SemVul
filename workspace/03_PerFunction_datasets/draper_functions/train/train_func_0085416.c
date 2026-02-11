sis630_set_eq(struct net_device *net_dev, u8 revision)
{
	struct sis900_private *sis_priv = netdev_priv(net_dev);
	u16 reg14h, eq_value=0, max_value=0, min_value=0;
	int i, maxcount=10;

	if ( !(revision == SIS630E_900_REV || revision == SIS630EA1_900_REV ||
	       revision == SIS630A_900_REV || revision ==  SIS630ET_900_REV) )
		return;

	if (netif_carrier_ok(net_dev)) {
		reg14h = mdio_read(net_dev, sis_priv->cur_phy, MII_RESV);
		mdio_write(net_dev, sis_priv->cur_phy, MII_RESV,
					(0x2200 | reg14h) & 0xBFFF);
		for (i=0; i < maxcount; i++) {
			eq_value = (0x00F8 & mdio_read(net_dev,
					sis_priv->cur_phy, MII_RESV)) >> 3;
			if (i == 0)
				max_value=min_value=eq_value;
			max_value = (eq_value > max_value) ?
						eq_value : max_value;
			min_value = (eq_value < min_value) ?
						eq_value : min_value;
		}

		if (revision == SIS630E_900_REV || revision == SIS630EA1_900_REV ||
		    revision == SIS630ET_900_REV) {
			if (max_value < 5)
				eq_value = max_value;
			else if (max_value >= 5 && max_value < 15)
				eq_value = (max_value == min_value) ?
						max_value+2 : max_value+1;
			else if (max_value >= 15)
				eq_value=(max_value == min_value) ?
						max_value+6 : max_value+5;
		}

		if (revision == SIS630A_900_REV &&
		    (sis_priv->host_bridge_rev == SIS630B0 ||
		     sis_priv->host_bridge_rev == SIS630B1)) {
			if (max_value == 0)
				eq_value = 3;
			else
				eq_value = (max_value + min_value + 1)/2;
		}

		reg14h = mdio_read(net_dev, sis_priv->cur_phy, MII_RESV);
		reg14h = (reg14h & 0xFF07) | ((eq_value << 3) & 0x00F8);
		reg14h = (reg14h | 0x6000) & 0xFDFF;
		mdio_write(net_dev, sis_priv->cur_phy, MII_RESV, reg14h);
	} else {
		reg14h = mdio_read(net_dev, sis_priv->cur_phy, MII_RESV);
		if (revision == SIS630A_900_REV &&
		    (sis_priv->host_bridge_rev == SIS630B0 ||
		     sis_priv->host_bridge_rev == SIS630B1))
			mdio_write(net_dev, sis_priv->cur_phy, MII_RESV,
						(reg14h | 0x2200) & 0xBFFF);
		else
			mdio_write(net_dev, sis_priv->cur_phy, MII_RESV,
						(reg14h | 0x2000) & 0xBFFF);
	}
}
