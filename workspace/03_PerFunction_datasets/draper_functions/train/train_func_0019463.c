prism54_get_mac(struct net_device *ndev, struct iw_request_info *info,
		struct iw_point *dwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	struct islpci_acl *acl = &priv->acl;
	struct mac_entry *entry;
	struct sockaddr *dst = (struct sockaddr *) extra;

	dwrq->length = 0;

	if (mutex_lock_interruptible(&acl->lock))
		return -ERESTARTSYS;

	list_for_each_entry(entry, &acl->mac_list, _list) {
		memcpy(dst->sa_data, entry->addr, ETH_ALEN);
		dst->sa_family = ARPHRD_ETHER;
		dwrq->length++;
		dst++;
	}
	mutex_unlock(&acl->lock);
	return 0;
}
