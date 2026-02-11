vxge_fw_flash(struct net_device *dev, struct ethtool_flash *parms)
{
	struct vxgedev *vdev = netdev_priv(dev);

	if (vdev->max_vpath_supported != VXGE_HW_MAX_VIRTUAL_PATHS) {
		printk(KERN_INFO "Single Function Mode is required to flash the"
		       " firmware\n");
		return -EINVAL;
	}

	if (netif_running(dev)) {
		printk(KERN_INFO "Interface %s must be down to flash the "
		       "firmware\n", dev->name);
		return -EBUSY;
	}

	return vxge_fw_upgrade(vdev, parms->data, 1);
}
