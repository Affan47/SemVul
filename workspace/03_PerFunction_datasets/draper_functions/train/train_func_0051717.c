auto_deepsleep_timer_fn(unsigned long data)
{
	struct lbs_private *priv = (struct lbs_private *)data;

	lbs_deb_enter(LBS_DEB_CMD);

	if (priv->is_activity_detected) {
		priv->is_activity_detected = 0;
	} else {
		if (priv->is_auto_deep_sleep_enabled &&
		    (!priv->wakeup_dev_required) &&
		    (priv->connect_status != LBS_CONNECTED)) {
			struct cmd_header cmd;

			lbs_deb_main("Entering auto deep sleep mode...\n");
			memset(&cmd, 0, sizeof(cmd));
			cmd.size = cpu_to_le16(sizeof(cmd));
			lbs_cmd_async(priv, CMD_802_11_DEEP_SLEEP, &cmd,
					sizeof(cmd));
		}
	}
	mod_timer(&priv->auto_deepsleep_timer , jiffies +
				(priv->auto_deep_sleep_timeout * HZ)/1000);
	lbs_deb_leave(LBS_DEB_CMD);
}
