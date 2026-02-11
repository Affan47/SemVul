mwl8k_finalize_join_worker(struct work_struct *work)
{
	struct mwl8k_priv *priv =
		container_of(work, struct mwl8k_priv, finalize_join_worker);
	struct sk_buff *skb = priv->beacon_skb;
	struct ieee80211_mgmt *mgmt = (void *)skb->data;
	int len = skb->len - offsetof(struct ieee80211_mgmt, u.beacon.variable);
	const u8 *tim = cfg80211_find_ie(WLAN_EID_TIM,
					 mgmt->u.beacon.variable, len);
	int dtim_period = 1;

	if (tim && tim[1] >= 2)
		dtim_period = tim[3];

	mwl8k_cmd_finalize_join(priv->hw, skb->data, skb->len, dtim_period);

	dev_kfree_skb(skb);
	priv->beacon_skb = NULL;
}
