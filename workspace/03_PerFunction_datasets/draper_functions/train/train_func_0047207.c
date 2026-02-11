cw1200_tx_h_action(struct cw1200_common *priv,
		   struct cw1200_txinfo *t)
{
	struct ieee80211_mgmt *mgmt =
		(struct ieee80211_mgmt *)t->hdr;
	if (ieee80211_is_action(t->hdr->frame_control) &&
	    mgmt->u.action.category == WLAN_CATEGORY_BACK)
		return 1;
	else
		return 0;
}
