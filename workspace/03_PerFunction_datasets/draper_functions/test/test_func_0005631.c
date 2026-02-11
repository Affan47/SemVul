ath10k_mac_can_set_bitrate_mask(struct ath10k *ar,
				enum ieee80211_band band,
				const struct cfg80211_bitrate_mask *mask)
{
	int i;
	u16 vht_mcs;


	for (i = 0; i < NL80211_VHT_NSS_MAX; i++) {
		vht_mcs = mask->control[band].vht_mcs[i];

		switch (vht_mcs) {
		case 0:
		case BIT(8) - 1:
		case BIT(9) - 1:
		case BIT(10) - 1:
			break;
		default:
			ath10k_warn(ar, "refusing bitrate mask with missing 0-7 VHT MCS rates\n");
			return false;
		}
	}

	return true;
}
