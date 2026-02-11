mwifiex_close(struct net_device *dev)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);

	if (priv->scan_request) {
		mwifiex_dbg(priv->adapter, INFO,
			    "aborting scan on ndo_stop\n");
		cfg80211_scan_done(priv->scan_request, 1);
		priv->scan_request = NULL;
		priv->scan_aborting = true;
	}

	mwifiex_set_led(priv->adapter, MWIFIEX_LED_OFF);
	return 0;
}
