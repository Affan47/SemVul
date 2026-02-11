cxgbi_device_find_by_netdev_rcu(struct net_device *ndev,
						     int *port)
{
	struct net_device *vdev = NULL;
	struct cxgbi_device *cdev;
	int i;

	if (ndev->priv_flags & IFF_802_1Q_VLAN) {
		vdev = ndev;
		ndev = vlan_dev_real_dev(ndev);
		pr_info("vlan dev %s -> %s.\n", vdev->name, ndev->name);
	}

	rcu_read_lock();
	list_for_each_entry_rcu(cdev, &cdev_rcu_list, rcu_node) {
		for (i = 0; i < cdev->nports; i++) {
			if (ndev == cdev->ports[i]) {
				cdev->hbas[i]->vdev = vdev;
				rcu_read_unlock();
				if (port)
					*port = i;
				return cdev;
			}
		}
	}
	rcu_read_unlock();

	log_debug(1 << CXGBI_DBG_DEV,
		  "ndev 0x%p, %s, NO match found.\n", ndev, ndev->name);
	return NULL;
}
