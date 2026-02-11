comet_timer(unsigned long data)
{
	struct net_device *dev = (struct net_device *)data;
	struct tulip_private *tp = netdev_priv(dev);
	int next_tick = 2*HZ;

	if (tulip_debug > 1)
		netdev_dbg(dev, "Comet link status %04x partner capability %04x\n",
			   tulip_mdio_read(dev, tp->phys[0], 1),
			   tulip_mdio_read(dev, tp->phys[0], 5));


	if (tulip_check_duplex(dev) < 0)
		{ netif_carrier_off(dev); }
	else
		{ netif_carrier_on(dev); }
	mod_timer(&tp->timer, RUN_AT(next_tick));
}
