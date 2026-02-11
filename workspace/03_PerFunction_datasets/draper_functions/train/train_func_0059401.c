mt7601u_mac_set_ampdu_factor(struct mt7601u_dev *dev)
{
	struct ieee80211_sta *sta;
	struct mt76_wcid *wcid;
	void *msta;
	u8 min_factor = 3;
	int i;

	rcu_read_lock();
	for (i = 0; i < ARRAY_SIZE(dev->wcid); i++) {
		wcid = rcu_dereference(dev->wcid[i]);
		if (!wcid)
			continue;

		msta = container_of(wcid, struct mt76_sta, wcid);
		sta = container_of(msta, struct ieee80211_sta, drv_priv);

		min_factor = min(min_factor, sta->ht_cap.ampdu_factor);
	}
	rcu_read_unlock();

	mt7601u_wr(dev, MT_MAX_LEN_CFG, 0xa0fff |
		   MT76_SET(MT_MAX_LEN_CFG_AMPDU, min_factor));
}
