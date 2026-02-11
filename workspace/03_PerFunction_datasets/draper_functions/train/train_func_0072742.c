prism2_ioctl_giwencode(struct net_device *dev,
				  struct iw_request_info *info,
				  struct iw_point *erq, char *key)
{
	struct hostap_interface *iface;
	local_info_t *local;
	int i, len;
	u16 val;
	struct lib80211_crypt_data *crypt;

	iface = netdev_priv(dev);
	local = iface->local;

	i = erq->flags & IW_ENCODE_INDEX;
	if (i < 1 || i > 4)
		i = local->crypt_info.tx_keyidx;
	else
		i--;
	if (i < 0 || i >= WEP_KEYS)
		return -EINVAL;

	crypt = local->crypt_info.crypt[i];
	erq->flags = i + 1;

	if (crypt == NULL || crypt->ops == NULL) {
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		return 0;
	}

	if (strcmp(crypt->ops->name, "WEP") != 0) {


		erq->length = 0;
		erq->flags |= IW_ENCODE_ENABLED;
		return 0;
	}


	len = crypt->ops->get_key(key, WEP_KEY_LEN, NULL, crypt->priv);
	erq->length = (len >= 0 ? len : 0);

	if (local->func->get_rid(dev, HFA384X_RID_CNFWEPFLAGS, &val, 2, 1) < 0)
	{
		printk("CNFWEPFLAGS reading failed\n");
		return -EOPNOTSUPP;
	}
	le16_to_cpus(&val);
	if (val & HFA384X_WEPFLAGS_PRIVACYINVOKED)
		erq->flags |= IW_ENCODE_ENABLED;
	else
		erq->flags |= IW_ENCODE_DISABLED;
	if (val & HFA384X_WEPFLAGS_EXCLUDEUNENCRYPTED)
		erq->flags |= IW_ENCODE_RESTRICTED;
	else
		erq->flags |= IW_ENCODE_OPEN;

	return 0;
}
