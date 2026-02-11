prism2_ioctl_giwretry(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_param *rrq, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;
	__le16 shortretry, longretry, lifetime, altretry;

	iface = netdev_priv(dev);
	local = iface->local;

	if (local->func->get_rid(dev, HFA384X_RID_SHORTRETRYLIMIT, &shortretry,
				 2, 1) < 0 ||
	    local->func->get_rid(dev, HFA384X_RID_LONGRETRYLIMIT, &longretry,
				 2, 1) < 0 ||
	    local->func->get_rid(dev, HFA384X_RID_MAXTRANSMITLIFETIME,
				 &lifetime, 2, 1) < 0)
		return -EINVAL;

	rrq->disabled = 0;

	if ((rrq->flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME) {
		rrq->flags = IW_RETRY_LIFETIME;
		rrq->value = le16_to_cpu(lifetime) * 1024;
	} else {
		if (local->manual_retry_count >= 0) {
			rrq->flags = IW_RETRY_LIMIT;
			if (local->func->get_rid(dev,
						 HFA384X_RID_CNFALTRETRYCOUNT,
						 &altretry, 2, 1) >= 0)
				rrq->value = le16_to_cpu(altretry);
			else
				rrq->value = local->manual_retry_count;
		} else if ((rrq->flags & IW_RETRY_LONG)) {
			rrq->flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
			rrq->value = le16_to_cpu(longretry);
		} else {
			rrq->flags = IW_RETRY_LIMIT;
			rrq->value = le16_to_cpu(shortretry);
			if (shortretry != longretry)
				rrq->flags |= IW_RETRY_SHORT;
		}
	}
	return 0;
}
