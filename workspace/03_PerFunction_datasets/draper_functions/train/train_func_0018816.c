cw1200_scan_complete_cb(struct cw1200_common *priv,
				struct wsm_scan_complete *arg)
{
	if (priv->mode == NL80211_IFTYPE_UNSPECIFIED)

		return;

	if (cancel_delayed_work_sync(&priv->scan.timeout) > 0) {
		priv->scan.status = 1;
		queue_delayed_work(priv->workqueue, &priv->scan.timeout, 0);
	}
}
