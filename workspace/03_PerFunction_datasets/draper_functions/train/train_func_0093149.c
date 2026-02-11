mt76_mac_shared_key_setup(struct mt7601u_dev *dev, u8 vif_idx, u8 key_idx,
			      struct ieee80211_key_conf *key)
{
	enum mt76_cipher_type cipher;
	u8 key_data[32];
	u32 val;

	cipher = mt76_mac_get_key_info(key, key_data);
	if (cipher == MT_CIPHER_NONE && key)
		return -EINVAL;

	trace_set_shared_key(dev, vif_idx, key_idx);

	mt7601u_wr_copy(dev, MT_SKEY(vif_idx, key_idx),
			key_data, sizeof(key_data));

	val = mt76_rr(dev, MT_SKEY_MODE(vif_idx));
	val &= ~(MT_SKEY_MODE_MASK << MT_SKEY_MODE_SHIFT(vif_idx, key_idx));
	val |= cipher << MT_SKEY_MODE_SHIFT(vif_idx, key_idx);
	mt76_wr(dev, MT_SKEY_MODE(vif_idx), val);

	return 0;
}
