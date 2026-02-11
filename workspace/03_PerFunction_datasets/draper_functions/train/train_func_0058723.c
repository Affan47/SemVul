ipw_wx_get_essid(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);


	mutex_lock(&priv->mutex);
	if (priv->config & CFG_STATIC_ESSID ||
	    priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING)) {
		IPW_DEBUG_WX("Getting essid: '%*pE'\n",
			     priv->essid_len, priv->essid);
		memcpy(extra, priv->essid, priv->essid_len);
		wrqu->essid.length = priv->essid_len;
		wrqu->essid.flags = 1;
	} else {
		IPW_DEBUG_WX("Getting essid: ANY\n");
		wrqu->essid.length = 0;
		wrqu->essid.flags = 0;
	}
	mutex_unlock(&priv->mutex);
	return 0;
}
