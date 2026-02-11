rt2x00crypto_create_tx_descriptor(struct rt2x00_dev *rt2x00dev,
				       struct sk_buff *skb,
				       struct txentry_desc *txdesc)
{
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	struct ieee80211_key_conf *hw_key = tx_info->control.hw_key;

	if (!rt2x00_has_cap_hw_crypto(rt2x00dev) || !hw_key)
		return;

	__set_bit(ENTRY_TXD_ENCRYPT, &txdesc->flags);

	txdesc->cipher = rt2x00crypto_key_to_cipher(hw_key);

	if (hw_key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		__set_bit(ENTRY_TXD_ENCRYPT_PAIRWISE, &txdesc->flags);

	txdesc->key_idx = hw_key->hw_key_idx;
	txdesc->iv_offset = txdesc->header_length;
	txdesc->iv_len = hw_key->iv_len;

	if (!(hw_key->flags & IEEE80211_KEY_FLAG_GENERATE_IV))
		__set_bit(ENTRY_TXD_ENCRYPT_IV, &txdesc->flags);

	if (!(hw_key->flags & IEEE80211_KEY_FLAG_GENERATE_MMIC))
		__set_bit(ENTRY_TXD_ENCRYPT_MMIC, &txdesc->flags);
}
