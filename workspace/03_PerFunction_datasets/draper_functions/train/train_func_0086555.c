ath10k_mac_bitrate_mask_get_single_rate(struct ath10k *ar,
					enum ieee80211_band band,
					const struct cfg80211_bitrate_mask *mask,
					u8 *rate, u8 *nss)
{
	struct ieee80211_supported_band *sband = &ar->mac.sbands[band];
	int rate_idx;
	int i;
	u16 bitrate;
	u8 preamble;
	u8 hw_rate;

	if (hweight32(mask->control[band].legacy) == 1) {
		rate_idx = ffs(mask->control[band].legacy) - 1;

		hw_rate = sband->bitrates[rate_idx].hw_value;
		bitrate = sband->bitrates[rate_idx].bitrate;

		if (ath10k_mac_bitrate_is_cck(bitrate))
			preamble = WMI_RATE_PREAMBLE_CCK;
		else
			preamble = WMI_RATE_PREAMBLE_OFDM;

		*nss = 1;
		*rate = preamble << 6 |
			(*nss - 1) << 4 |
			hw_rate << 0;

		return 0;
	}

	for (i = 0; i < ARRAY_SIZE(mask->control[band].ht_mcs); i++) {
		if (hweight8(mask->control[band].ht_mcs[i]) == 1) {
			*nss = i + 1;
			*rate = WMI_RATE_PREAMBLE_HT << 6 |
				(*nss - 1) << 4 |
				(ffs(mask->control[band].ht_mcs[i]) - 1);

			return 0;
		}
	}

	for (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++) {
		if (hweight16(mask->control[band].vht_mcs[i]) == 1) {
			*nss = i + 1;
			*rate = WMI_RATE_PREAMBLE_VHT << 6 |
				(*nss - 1) << 4 |
				(ffs(mask->control[band].vht_mcs[i]) - 1);

			return 0;
		}
	}

	return -EINVAL;
}
