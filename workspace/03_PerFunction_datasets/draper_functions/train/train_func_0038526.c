ath9k_htc_ampdu_action(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif,
				  struct ieee80211_ampdu_params *params)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath9k_htc_sta *ista;
	int ret = 0;
	struct ieee80211_sta *sta = params->sta;
	enum ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	switch (action) {
	case IEEE80211_AMPDU_RX_START:
		break;
	case IEEE80211_AMPDU_RX_STOP:
		break;
	case IEEE80211_AMPDU_TX_START:
		ret = ath9k_htc_tx_aggr_oper(priv, vif, sta, action, tid);
		if (!ret)
			ieee80211_start_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;
	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		ath9k_htc_tx_aggr_oper(priv, vif, sta, action, tid);
		ieee80211_stop_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		ista = (struct ath9k_htc_sta *) sta->drv_priv;
		spin_lock_bh(&priv->tx.tx_lock);
		ista->tid_state[tid] = AGGR_OPERATIONAL;
		spin_unlock_bh(&priv->tx.tx_lock);
		break;
	default:
		ath_err(ath9k_hw_common(priv->ah), "Unknown AMPDU action\n");
	}

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	return ret;
}
