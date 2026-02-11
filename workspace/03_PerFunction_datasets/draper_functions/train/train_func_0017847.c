mwl8k_encapsulate_tx_frame(struct mwl8k_priv *priv,
		struct sk_buff *skb)
{
	struct ieee80211_hdr *wh;
	struct ieee80211_tx_info *tx_info;
	struct ieee80211_key_conf *key_conf;
	int data_pad;
	int head_pad = 0;

	wh = (struct ieee80211_hdr *)skb->data;

	tx_info = IEEE80211_SKB_CB(skb);

	key_conf = NULL;
	if (ieee80211_is_data(wh->frame_control))
		key_conf = tx_info->control.hw_key;


	data_pad = 0;
	if (key_conf != NULL) {
		head_pad = key_conf->iv_len;
		switch (key_conf->cipher) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
			data_pad = 4;
			break;
		case WLAN_CIPHER_SUITE_TKIP:
			data_pad = 12;
			break;
		case WLAN_CIPHER_SUITE_CCMP:
			data_pad = 8;
			break;
		}
	}
	mwl8k_add_dma_header(priv, skb, head_pad, data_pad);
}
