lbs_host_to_card_done(struct lbs_private *priv)
{
	unsigned long flags;

	lbs_deb_enter(LBS_DEB_THREAD);

	spin_lock_irqsave(&priv->driver_lock, flags);
	del_timer(&priv->tx_lockup_timer);

	priv->dnld_sent = DNLD_RES_RECEIVED;


	if (!priv->cur_cmd || priv->tx_pending_len > 0) {
		if (!priv->wakeup_dev_required)
			wake_up(&priv->waitq);
	}

	spin_unlock_irqrestore(&priv->driver_lock, flags);
	lbs_deb_leave(LBS_DEB_THREAD);
}
