prism2_ioctl_siwessid(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_point *data, char *ssid)
{
	struct hostap_interface *iface;
	local_info_t *local;

	iface = netdev_priv(dev);
	local = iface->local;

	if (iface->type == HOSTAP_INTERFACE_WDS)
		return -EOPNOTSUPP;

	if (data->flags == 0)
		ssid[0] = '\0';

	if (local->iw_mode == IW_MODE_MASTER && ssid[0] == '\0') {


		printk(KERN_DEBUG "%s: Host AP mode does not support "
		       "'Any' essid\n", dev->name);
		return -EINVAL;
	}

	memcpy(local->essid, ssid, data->length);
	local->essid[data->length] = '\0';

	if ((!local->fw_ap &&
	     hostap_set_string(dev, HFA384X_RID_CNFDESIREDSSID, local->essid))
	    || hostap_set_string(dev, HFA384X_RID_CNFOWNSSID, local->essid) ||
	    local->func->reset_port(dev))
		return -EINVAL;

	return 0;
}
