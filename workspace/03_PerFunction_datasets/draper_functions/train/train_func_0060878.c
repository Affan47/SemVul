ipw2100_wx_get_wap(struct net_device *dev,
			      struct iw_request_info *info,
			      union iwreq_data *wrqu, char *extra)
{


	struct ipw2100_priv *priv = libipw_priv(dev);


	if (priv->config & CFG_STATIC_BSSID || priv->status & STATUS_ASSOCIATED) {
		wrqu->ap_addr.sa_family = ARPHRD_ETHER;
		memcpy(wrqu->ap_addr.sa_data, priv->bssid, ETH_ALEN);
	} else
		eth_zero_addr(wrqu->ap_addr.sa_data);

	IPW_DEBUG_WX("Getting WAP BSSID: %pM\n", wrqu->ap_addr.sa_data);
	return 0;
}
