rt2x00mac_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
		      struct ieee80211_vif *vif, struct ieee80211_sta *sta,
		      struct ieee80211_key_conf *key)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	int (*set_key) (struct rt2x00_dev *rt2x00dev,
			struct rt2x00lib_crypto *crypto,
			struct ieee80211_key_conf *key);
	struct rt2x00lib_crypto crypto;
	static const u8 bcast_addr[ETH_ALEN] =
		{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, };
	struct rt2x00_sta *sta_priv = NULL;

	if (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		return 0;

	if (!rt2x00_has_cap_hw_crypto(rt2x00dev))
		return -EOPNOTSUPP;


	if (vif->type == NL80211_IFTYPE_ADHOC &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		return -EOPNOTSUPP;

	if (key->keylen > 32)
		return -ENOSPC;

	memset(&crypto, 0, sizeof(crypto));

	crypto.bssidx = rt2x00lib_get_bssidx(rt2x00dev, vif);
	crypto.cipher = rt2x00crypto_key_to_cipher(key);
	if (crypto.cipher == CIPHER_NONE)
		return -EOPNOTSUPP;
	if (crypto.cipher == CIPHER_TKIP && rt2x00_is_usb(rt2x00dev))
		return -EOPNOTSUPP;

	crypto.cmd = cmd;

	if (sta) {
		crypto.address = sta->addr;
		sta_priv = sta_to_rt2x00_sta(sta);
		crypto.wcid = sta_priv->wcid;
	} else
		crypto.address = bcast_addr;

	if (crypto.cipher == CIPHER_TKIP)
		memcpy_tkip(&crypto, &key->key[0], key->keylen);
	else
		memcpy(crypto.key, &key->key[0], key->keylen);


	if (cmd == SET_KEY)
		key->hw_key_idx = 0;

	if (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		set_key = rt2x00dev->ops->lib->config_pairwise_key;
	else
		set_key = rt2x00dev->ops->lib->config_shared_key;

	if (!set_key)
		return -EOPNOTSUPP;

	return set_key(rt2x00dev, &crypto, key);
}
