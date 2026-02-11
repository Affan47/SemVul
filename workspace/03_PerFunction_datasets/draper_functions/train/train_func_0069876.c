mwl8k_save_beacon(struct ieee80211_hw *hw,
				     struct sk_buff *skb)
{
	struct mwl8k_priv *priv = hw->priv;

	priv->capture_beacon = false;
	eth_zero_addr(priv->capture_bssid);


	priv->beacon_skb = skb_copy(skb, GFP_ATOMIC);
	if (priv->beacon_skb != NULL)
		ieee80211_queue_work(hw, &priv->finalize_join_worker);
}
