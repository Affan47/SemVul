atmel_get_essid(struct net_device *dev,
			   struct iw_request_info *info,
			   struct iw_point *dwrq,
			   char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);


	if (priv->new_SSID_size != 0) {
		memcpy(extra, priv->new_SSID, priv->new_SSID_size);
		dwrq->length = priv->new_SSID_size;
	} else {
		memcpy(extra, priv->SSID, priv->SSID_size);
		dwrq->length = priv->SSID_size;
	}

	dwrq->flags = !priv->connect_to_any_BSS;

	return 0;
}
