wil_find_tx_bcast(struct wil6210_priv *wil,
				       struct sk_buff *skb)
{
	struct wireless_dev *wdev = wil->wdev;

	if (wdev->iftype != NL80211_IFTYPE_AP)
		return wil_find_tx_bcast_2(wil, skb);

	return wil_find_tx_bcast_1(wil, skb);
}
