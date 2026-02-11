ipw_link_down(struct ipw_priv *priv)
{
	ipw_led_link_down(priv);
	netif_carrier_off(priv->net_dev);
	notify_wx_assoc_event(priv);


	cancel_delayed_work(&priv->request_scan);
	cancel_delayed_work(&priv->request_direct_scan);
	cancel_delayed_work(&priv->request_passive_scan);
	cancel_delayed_work(&priv->adhoc_check);
	cancel_delayed_work(&priv->gather_stats);

	ipw_reset_stats(priv);

	if (!(priv->status & STATUS_EXIT_PENDING)) {

		schedule_delayed_work(&priv->request_scan, 0);
	} else
		cancel_delayed_work(&priv->scan_event);
}
