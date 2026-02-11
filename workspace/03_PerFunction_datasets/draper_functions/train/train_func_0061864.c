link_report(struct net_device *dev)
{
	if (!netif_carrier_ok(dev))
		netdev_info(dev, "link down\n");
	else {
		static const char *fc[] = { "no", "Rx", "Tx", "Tx/Rx" };

		const char *s;
		const struct port_info *p = netdev_priv(dev);

		switch (p->link_cfg.speed) {
		case 10000:
			s = "10Gbps";
			break;
		case 1000:
			s = "1000Mbps";
			break;
		case 100:
			s = "100Mbps";
			break;
		case 40000:
			s = "40Gbps";
			break;
		default:
			pr_info("%s: unsupported speed: %d\n",
				dev->name, p->link_cfg.speed);
			return;
		}

		netdev_info(dev, "link up, %s, full-duplex, %s PAUSE\n", s,
			    fc[p->link_cfg.fc]);
	}
}
