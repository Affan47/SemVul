ath5k_hw_noise_floor_calibration(struct ath5k_hw *ah, short freq)
{
	int ret;
	unsigned int i;
	s32 noise_floor;


	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGCCTL,
				AR5K_PHY_AGCCTL_NF);

	ret = ath5k_hw_register_timeout(ah, AR5K_PHY_AGCCTL,
			AR5K_PHY_AGCCTL_NF, 0, 0);

	if (ret) {
		DBG("ath5k: noise floor calibration timeout (%d MHz)\n", freq);
		return -EAGAIN;
	}


	for (i = 20; i > 0; i--) {
		mdelay(1);
		noise_floor = ath5k_hw_reg_read(ah, AR5K_PHY_NF);
		noise_floor = AR5K_PHY_NF_RVAL(noise_floor);
		if (noise_floor & AR5K_PHY_NF_ACTIVE) {
			noise_floor = AR5K_PHY_NF_AVAL(noise_floor);

			if (noise_floor <= AR5K_TUNE_NOISE_FLOOR)
				break;
		}
	}

	DBG2("ath5k: noise floor %d\n", noise_floor);

	if (noise_floor > AR5K_TUNE_NOISE_FLOOR) {
		DBG("ath5k: noise floor calibration failed (%d MHz)\n", freq);
		return -EAGAIN;
	}

	ah->ah_noise_floor = noise_floor;

	return 0;
}
