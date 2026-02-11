carl9170_op_tx(struct ieee80211_hw *hw,
		    struct ieee80211_tx_control *control,
		    struct sk_buff *skb)
{
	struct ar9170 *ar = hw->priv;
	struct ieee80211_tx_info *info;
	struct ieee80211_sta *sta = control->sta;
	struct ieee80211_vif *vif;
	bool run;

	if (unlikely(!IS_STARTED(ar)))
		goto err_free;

	info = IEEE80211_SKB_CB(skb);
	vif = info->control.vif;

	if (unlikely(carl9170_tx_prepare(ar, sta, skb)))
		goto err_free;

	carl9170_tx_accounting(ar, skb);


	if (sta) {
		struct carl9170_sta_info *stai = (void *) sta->drv_priv;
		atomic_inc(&stai->pending_frames);
	}

	if (info->flags & IEEE80211_TX_CTL_AMPDU) {


		run = carl9170_tx_ampdu_queue(ar, sta, skb, info);
		if (run)
			carl9170_tx_ampdu(ar);

	} else {
		unsigned int queue = skb_get_queue_mapping(skb);

		carl9170_tx_get_rates(ar, vif, sta, skb);
		carl9170_tx_apply_rateset(ar, info, skb);
		skb_queue_tail(&ar->tx_pending[queue], skb);
	}

	carl9170_tx(ar);
	return;

err_free:
	ar->tx_dropped++;
	ieee80211_free_txskb(ar->hw, skb);
}
