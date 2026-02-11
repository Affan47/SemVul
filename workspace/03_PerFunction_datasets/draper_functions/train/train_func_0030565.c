xennet_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	struct netfront_info *np = netdev_priv(dev);
	int val;

	if (features & NETIF_F_SG) {
		if (xenbus_scanf(XBT_NIL, np->xbdev->otherend, "feature-sg",
				 "%d", &val) < 0)
			val = 0;

		if (!val)
			features &= ~NETIF_F_SG;
	}

	if (features & NETIF_F_IPV6_CSUM) {
		if (xenbus_scanf(XBT_NIL, np->xbdev->otherend,
				 "feature-ipv6-csum-offload", "%d", &val) < 0)
			val = 0;

		if (!val)
			features &= ~NETIF_F_IPV6_CSUM;
	}

	if (features & NETIF_F_TSO) {
		if (xenbus_scanf(XBT_NIL, np->xbdev->otherend,
				 "feature-gso-tcpv4", "%d", &val) < 0)
			val = 0;

		if (!val)
			features &= ~NETIF_F_TSO;
	}

	if (features & NETIF_F_TSO6) {
		if (xenbus_scanf(XBT_NIL, np->xbdev->otherend,
				 "feature-gso-tcpv6", "%d", &val) < 0)
			val = 0;

		if (!val)
			features &= ~NETIF_F_TSO6;
	}

	return features;
}
