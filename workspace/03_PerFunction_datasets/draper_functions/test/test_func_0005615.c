prism2_ioctl_giwscan(struct net_device *dev,
				struct iw_request_info *info,
				struct iw_point *data, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;
	int res;

	iface = netdev_priv(dev);
	local = iface->local;

	if (local->iw_mode == IW_MODE_MASTER) {


		res = prism2_ap_translate_scan(dev, info, extra);
		if (res >= 0) {
			printk(KERN_DEBUG "Scan result translation succeeded "
			       "(length=%d)\n", res);
			data->length = res;
			return 0;
		} else {
			printk(KERN_DEBUG
			       "Scan result translation failed (res=%d)\n",
			       res);
			data->length = 0;
			return res;
		}
	} else {

		return prism2_ioctl_giwscan_sta(dev, info, data, extra);
	}
}
