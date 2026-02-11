ath5k_hw_rf_check_gainf_readback(struct ath5k_hw *ah)
{
	const struct ath5k_rf_reg *rf_regs;
	u32 step, mix_ovr, level[4];

	if (ah->ah_rf_banks == NULL)
		return 0;

	if (ah->ah_radio == AR5K_RF5111) {

		rf_regs = rf_regs_5111;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5111);

		step = ath5k_hw_rfb_op(ah, rf_regs, 0, AR5K_RF_RFGAIN_STEP,
			0);

		level[0] = 0;
		level[1] = (step == 63) ? 50 : step + 4;
		level[2] = (step != 63) ? 64 : level[0];
		level[3] = level[2] + 50 ;

		ah->ah_gain.g_high = level[3] -
			(step == 63 ? AR5K_GAIN_DYN_ADJUST_HI_MARGIN : -5);
		ah->ah_gain.g_low = level[0] +
			(step == 63 ? AR5K_GAIN_DYN_ADJUST_LO_MARGIN : 0);
	} else {

		rf_regs = rf_regs_5112;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5112);

		mix_ovr = ath5k_hw_rfb_op(ah, rf_regs, 0, AR5K_RF_MIXVGA_OVR,
			0);

		level[0] = level[2] = 0;

		if (mix_ovr == 1) {
			level[1] = level[3] = 83;
		} else {
			level[1] = level[3] = 107;
			ah->ah_gain.g_high = 55;
		}
	}

	return (ah->ah_gain.g_current >= level[0] &&
			ah->ah_gain.g_current <= level[1]) ||
		(ah->ah_gain.g_current >= level[2] &&
			ah->ah_gain.g_current <= level[3]);
}
