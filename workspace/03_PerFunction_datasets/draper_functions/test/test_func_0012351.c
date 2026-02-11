ipw_wx_set_essid(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
        int length;

        mutex_lock(&priv->mutex);

        if (!wrqu->essid.flags)
        {
                IPW_DEBUG_WX("Setting ESSID to ANY\n");
                ipw_disassociate(priv);
                priv->config &= ~CFG_STATIC_ESSID;
                ipw_associate(priv);
                mutex_unlock(&priv->mutex);
                return 0;
        }

	length = min((int)wrqu->essid.length, IW_ESSID_MAX_SIZE);

	priv->config |= CFG_STATIC_ESSID;

	if (priv->essid_len == length && !memcmp(priv->essid, extra, length)
	    && (priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING))) {
		IPW_DEBUG_WX("ESSID set to current ESSID.\n");
		mutex_unlock(&priv->mutex);
		return 0;
	}

	IPW_DEBUG_WX("Setting ESSID: '%*pE' (%d)\n", length, extra, length);

	priv->essid_len = length;
	memcpy(priv->essid, extra, priv->essid_len);


	IPW_DEBUG_ASSOC("[re]association triggered due to ESSID change.\n");
	if (!ipw_disassociate(priv))
		ipw_associate(priv);

	mutex_unlock(&priv->mutex);
	return 0;
}
