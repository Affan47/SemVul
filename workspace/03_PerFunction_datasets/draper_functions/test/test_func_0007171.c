tulip_ethtool_set_wol(struct net_device *dev,
				 struct ethtool_wolinfo *wolinfo)
{
	struct tulip_private *tp = netdev_priv(dev);

	if (wolinfo->wolopts & (~tp->wolinfo.supported))
		   return -EOPNOTSUPP;

	tp->wolinfo.wolopts = wolinfo->wolopts;
	device_set_wakeup_enable(&tp->pdev->dev, tp->wolinfo.wolopts);
	return 0;
}
