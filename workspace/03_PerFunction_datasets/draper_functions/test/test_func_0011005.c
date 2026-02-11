sc92031_ethtool_nway_reset(struct net_device *dev)
{
	int err = 0;
	struct sc92031_priv *priv = netdev_priv(dev);
	void __iomem *port_base = priv->port_base;
	u16 bmcr;

	spin_lock_bh(&priv->lock);

	bmcr = _sc92031_mii_read(port_base, MII_BMCR);
	if (!(bmcr & BMCR_ANENABLE)) {
		err = -EINVAL;
		goto out;
	}

	_sc92031_mii_write(port_base, MII_BMCR, bmcr | BMCR_ANRESTART);

out:
	_sc92031_mii_scan(port_base);
	mmiowb();

	spin_unlock_bh(&priv->lock);

	return err;
}
