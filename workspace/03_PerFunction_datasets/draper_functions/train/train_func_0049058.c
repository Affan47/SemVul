ipw_wx_set_encode(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *key)
{
	struct ipw_priv *priv = libipw_priv(dev);
	int ret;
	u32 cap = priv->capability;

	mutex_lock(&priv->mutex);
	ret = libipw_wx_set_encode(priv->ieee, info, wrqu, key);


	if (cap != priv->capability &&
	    priv->ieee->iw_mode == IW_MODE_ADHOC &&
	    priv->status & STATUS_ASSOCIATED)
		ipw_disassociate(priv);

	mutex_unlock(&priv->mutex);
	return ret;
}
