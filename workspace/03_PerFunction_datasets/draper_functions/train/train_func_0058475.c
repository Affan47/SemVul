_internal_start_scan(struct lbs_private *priv, bool internal,
	struct cfg80211_scan_request *request)
{
	lbs_deb_enter(LBS_DEB_CFG80211);

	lbs_deb_scan("scan: ssids %d, channels %d, ie_len %zd\n",
		request->n_ssids, request->n_channels, request->ie_len);

	priv->scan_channel = 0;
	priv->scan_req = request;
	priv->internal_scan = internal;

	queue_delayed_work(priv->work_thread, &priv->scan_work,
		msecs_to_jiffies(50));

	lbs_deb_leave(LBS_DEB_CFG80211);
}
