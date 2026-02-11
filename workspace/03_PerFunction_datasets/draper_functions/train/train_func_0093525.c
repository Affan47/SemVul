mwifiex_del_rx_reorder_entry(struct mwifiex_private *priv,
			     struct mwifiex_rx_reorder_tbl *tbl)
{
	unsigned long flags;
	int start_win;

	if (!tbl)
		return;

	spin_lock_irqsave(&priv->adapter->rx_proc_lock, flags);
	priv->adapter->rx_locked = true;
	if (priv->adapter->rx_processing) {
		spin_unlock_irqrestore(&priv->adapter->rx_proc_lock, flags);
		flush_workqueue(priv->adapter->rx_workqueue);
	} else {
		spin_unlock_irqrestore(&priv->adapter->rx_proc_lock, flags);
	}

	start_win = (tbl->start_win + tbl->win_size) & (MAX_TID_VALUE - 1);
	mwifiex_11n_dispatch_pkt_until_start_win(priv, tbl, start_win);

	del_timer_sync(&tbl->timer_context.timer);
	tbl->timer_context.timer_is_set = false;

	spin_lock_irqsave(&priv->rx_reorder_tbl_lock, flags);
	list_del(&tbl->list);
	spin_unlock_irqrestore(&priv->rx_reorder_tbl_lock, flags);

	kfree(tbl->rx_reorder_ptr);
	kfree(tbl);

	spin_lock_irqsave(&priv->adapter->rx_proc_lock, flags);
	priv->adapter->rx_locked = false;
	spin_unlock_irqrestore(&priv->adapter->rx_proc_lock, flags);

}
