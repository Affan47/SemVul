lbs_init_adapter(struct lbs_private *priv)
{
	int ret;

	lbs_deb_enter(LBS_DEB_MAIN);

	eth_broadcast_addr(priv->current_addr);

	priv->connect_status = LBS_DISCONNECTED;
	priv->channel = DEFAULT_AD_HOC_CHANNEL;
	priv->mac_control = CMD_ACT_MAC_RX_ON | CMD_ACT_MAC_TX_ON;
	priv->radio_on = 1;
	priv->psmode = LBS802_11POWERMODECAM;
	priv->psstate = PS_STATE_FULL_POWER;
	priv->is_deep_sleep = 0;
	priv->is_auto_deep_sleep_enabled = 0;
	priv->deep_sleep_required = 0;
	priv->wakeup_dev_required = 0;
	init_waitqueue_head(&priv->ds_awake_q);
	init_waitqueue_head(&priv->scan_q);
	priv->authtype_auto = 1;
	priv->is_host_sleep_configured = 0;
	priv->is_host_sleep_activated = 0;
	init_waitqueue_head(&priv->host_sleep_q);
	init_waitqueue_head(&priv->fw_waitq);
	mutex_init(&priv->lock);

	setup_timer(&priv->command_timer, lbs_cmd_timeout_handler,
		(unsigned long)priv);
	setup_timer(&priv->tx_lockup_timer, lbs_tx_lockup_handler,
		(unsigned long)priv);
	setup_timer(&priv->auto_deepsleep_timer, auto_deepsleep_timer_fn,
			(unsigned long)priv);

	INIT_LIST_HEAD(&priv->cmdfreeq);
	INIT_LIST_HEAD(&priv->cmdpendingq);

	spin_lock_init(&priv->driver_lock);


	if (lbs_allocate_cmd_buffer(priv)) {
		pr_err("Out of memory allocating command buffers\n");
		ret = -ENOMEM;
		goto out;
	}
	priv->resp_idx = 0;
	priv->resp_len[0] = priv->resp_len[1] = 0;


	ret = kfifo_alloc(&priv->event_fifo, sizeof(u32) * 16, GFP_KERNEL);
	if (ret) {
		pr_err("Out of memory allocating event FIFO buffer\n");
		goto out;
	}

out:
	lbs_deb_leave_args(LBS_DEB_MAIN, "ret %d", ret);

	return ret;
}
