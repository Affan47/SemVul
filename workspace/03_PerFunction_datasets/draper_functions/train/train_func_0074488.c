macvlan_sync_address(struct net_device *dev, unsigned char *addr)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;
	int err;

	if (!(dev->flags & IFF_UP)) {

		ether_addr_copy(dev->dev_addr, addr);
	} else {

		if (macvlan_addr_busy(vlan->port, addr))
			return -EBUSY;

		if (!vlan->port->passthru) {
			err = dev_uc_add(lowerdev, addr);
			if (err)
				return err;

			dev_uc_del(lowerdev, dev->dev_addr);
		}

		macvlan_hash_change_addr(vlan, addr);
	}
	return 0;
}
