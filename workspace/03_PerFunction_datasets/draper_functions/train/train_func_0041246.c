cw1200_tx_h_pm_state(struct cw1200_common *priv,
		     struct cw1200_txinfo *t)
{
	int was_buffered = 1;

	if (t->txpriv.link_id == CW1200_LINK_ID_AFTER_DTIM &&
	    !priv->buffered_multicasts) {
		priv->buffered_multicasts = true;
		if (priv->sta_asleep_mask)
			queue_work(priv->workqueue,
				   &priv->multicast_start_work);
	}

	if (t->txpriv.raw_link_id && t->txpriv.tid < CW1200_MAX_TID)
		was_buffered = priv->link_id_db[t->txpriv.raw_link_id - 1].buffered[t->txpriv.tid]++;

	return !was_buffered;
}
