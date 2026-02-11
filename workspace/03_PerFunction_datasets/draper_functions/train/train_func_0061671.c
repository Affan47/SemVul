prism2_ioctl_siwrts(struct net_device *dev,
			       struct iw_request_info *info,
			       struct iw_param *rts, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;
	__le16 val;

	iface = netdev_priv(dev);
	local = iface->local;

	if (rts->disabled)
		val = cpu_to_le16(2347);
	else if (rts->value < 0 || rts->value > 2347)
		return -EINVAL;
	else
		val = cpu_to_le16(rts->value);

	if (local->func->set_rid(dev, HFA384X_RID_RTSTHRESHOLD, &val, 2) ||
	    local->func->reset_port(dev))
		return -EINVAL;

	local->rts_threshold = rts->value;

	return 0;
}
