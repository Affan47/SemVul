ipw2100_wx_set_frag(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{


	struct ipw2100_priv *priv = libipw_priv(dev);

	if (!wrqu->frag.fixed)
		return -EINVAL;

	if (wrqu->frag.disabled) {
		priv->frag_threshold |= FRAG_DISABLED;
		priv->ieee->fts = DEFAULT_FTS;
	} else {
		if (wrqu->frag.value < MIN_FRAG_THRESHOLD ||
		    wrqu->frag.value > MAX_FRAG_THRESHOLD)
			return -EINVAL;

		priv->ieee->fts = wrqu->frag.value & ~0x1;
		priv->frag_threshold = priv->ieee->fts;
	}

	IPW_DEBUG_WX("SET Frag Threshold -> %d\n", priv->ieee->fts);

	return 0;
}
