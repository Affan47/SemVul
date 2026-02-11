ath5k_hw_get_median_noise_floor(struct ath5k_hw *ah)
{
	s16 sort[ATH5K_NF_CAL_HIST_MAX];
	s16 tmp;
	int i, j;

	memcpy(sort, ah->ah_nfcal_hist.nfval, sizeof(sort));
	for (i = 0; i < ATH5K_NF_CAL_HIST_MAX - 1; i++) {
		for (j = 1; j < ATH5K_NF_CAL_HIST_MAX - i; j++) {
			if (sort[j] > sort[j - 1]) {
				tmp = sort[j];
				sort[j] = sort[j - 1];
				sort[j - 1] = tmp;
			}
		}
	}
	for (i = 0; i < ATH5K_NF_CAL_HIST_MAX; i++) {
		ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
			"cal %d:%d\n", i, sort[i]);
	}
	return sort[(ATH5K_NF_CAL_HIST_MAX - 1) / 2];
}
