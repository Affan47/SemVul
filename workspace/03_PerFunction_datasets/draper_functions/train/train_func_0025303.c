ath10k_htt_rx_crypto_tail_len(struct ath10k *ar,
					 enum htt_rx_mpdu_encrypt_type type)
{
	switch (type) {
	case HTT_RX_MPDU_ENCRYPT_NONE:
		return 0;
	case HTT_RX_MPDU_ENCRYPT_WEP40:
	case HTT_RX_MPDU_ENCRYPT_WEP104:
		return IEEE80211_WEP_ICV_LEN;
	case HTT_RX_MPDU_ENCRYPT_TKIP_WITHOUT_MIC:
	case HTT_RX_MPDU_ENCRYPT_TKIP_WPA:
		return IEEE80211_TKIP_ICV_LEN;
	case HTT_RX_MPDU_ENCRYPT_AES_CCM_WPA2:
		return IEEE80211_CCMP_MIC_LEN;
	case HTT_RX_MPDU_ENCRYPT_WEP128:
	case HTT_RX_MPDU_ENCRYPT_WAPI:
		break;
	}

	ath10k_warn(ar, "unsupported encryption type %d\n", type);
	return 0;
}
