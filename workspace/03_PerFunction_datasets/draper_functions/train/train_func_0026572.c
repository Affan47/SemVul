mwifiex_11n_find_last_seq_num(struct reorder_tmr_cnxt *ctx)
{
	struct mwifiex_rx_reorder_tbl *rx_reorder_tbl_ptr = ctx->ptr;
	struct mwifiex_private *priv = ctx->priv;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&priv->rx_reorder_tbl_lock, flags);
	for (i = rx_reorder_tbl_ptr->win_size - 1; i >= 0; --i) {
		if (rx_reorder_tbl_ptr->rx_reorder_ptr[i]) {
			spin_unlock_irqrestore(&priv->rx_reorder_tbl_lock,
					       flags);
			return i;
		}
	}
	spin_unlock_irqrestore(&priv->rx_reorder_tbl_lock, flags);

	return -1;
}
