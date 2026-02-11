ath_dynack_init(struct ath_hw *ah)
{
	struct ath_dynack *da = &ah->dynack;

	memset(da, 0, sizeof(struct ath_dynack));

	spin_lock_init(&da->qlock);
	INIT_LIST_HEAD(&da->nodes);

	ah->hw->wiphy->features |= NL80211_FEATURE_ACKTO_ESTIMATION;
}
