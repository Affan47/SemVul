cw1200_sta_remove(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		      struct ieee80211_sta *sta)
{
	struct cw1200_common *priv = hw->priv;
	struct cw1200_sta_priv *sta_priv =
			(struct cw1200_sta_priv *)&sta->drv_priv;
	struct cw1200_link_entry *entry;

	if (priv->mode != NL80211_IFTYPE_AP || !sta_priv->link_id)
		return 0;

	entry = &priv->link_id_db[sta_priv->link_id - 1];
	spin_lock_bh(&priv->ps_state_lock);
	entry->status = CW1200_LINK_RESERVE;
	entry->timestamp = jiffies;
	wsm_lock_tx_async(priv);
	if (queue_work(priv->workqueue, &priv->link_id_work) <= 0)
		wsm_unlock_tx(priv);
	spin_unlock_bh(&priv->ps_state_lock);
	flush_workqueue(priv->workqueue);
	return 0;
}
