cdc_mbim_rx_add_vid(struct net_device *netdev, __be16 proto, u16 vid)
{
	struct usbnet *dev = netdev_priv(netdev);
	struct cdc_mbim_state *info = (void *)&dev->data;


	if (vid == MBIM_IPS0_VID)
		info->flags |= FLAG_IPS0_VLAN;
	else
		if (vid >= 512)
			return -EINVAL;
	return 0;
}
