iwl_scan_cancel(struct iwl_priv *priv)
{
	IWL_DEBUG_SCAN(priv, "Queuing abort scan\n");
	queue_work(priv->workqueue, &priv->abort_scan);
	return 0;
}
