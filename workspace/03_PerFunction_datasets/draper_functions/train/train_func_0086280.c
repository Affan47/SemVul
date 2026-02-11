macvlan_stop(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;

	if (vlan->fwd_priv) {
		lowerdev->netdev_ops->ndo_dfwd_del_station(lowerdev,
							   vlan->fwd_priv);
		vlan->fwd_priv = NULL;
		return 0;
	}

	dev_uc_unsync(lowerdev, dev);
	dev_mc_unsync(lowerdev, dev);

	if (vlan->port->passthru) {
		if (!(vlan->flags & MACVLAN_FLAG_NOPROMISC))
			dev_set_promiscuity(lowerdev, -1);
		goto hash_del;
	}

	if (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(lowerdev, -1);

	if (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(lowerdev, -1);

	dev_uc_del(lowerdev, dev->dev_addr);

hash_del:
	macvlan_hash_del(vlan, !dev->dismantle);
	return 0;
}
