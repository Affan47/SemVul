ath9k_hw_ani_init(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ar5416AniState *ani = &ah->ani;

	ath_dbg(common, ANI, "Initialize ANI\n");

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		ah->config.ofdm_trig_high = ATH9K_ANI_OFDM_TRIG_HIGH;
		ah->config.ofdm_trig_low = ATH9K_ANI_OFDM_TRIG_LOW;
		ah->config.cck_trig_high = ATH9K_ANI_CCK_TRIG_HIGH;
		ah->config.cck_trig_low = ATH9K_ANI_CCK_TRIG_LOW;
	} else {
		ah->config.ofdm_trig_high = ATH9K_ANI_OFDM_TRIG_HIGH_OLD;
		ah->config.ofdm_trig_low = ATH9K_ANI_OFDM_TRIG_LOW_OLD;
		ah->config.cck_trig_high = ATH9K_ANI_CCK_TRIG_HIGH_OLD;
		ah->config.cck_trig_low = ATH9K_ANI_CCK_TRIG_LOW_OLD;
	}

	ani->spurImmunityLevel = ATH9K_ANI_SPUR_IMMUNE_LVL;
	ani->firstepLevel = ATH9K_ANI_FIRSTEP_LVL;
	ani->mrcCCK = AR_SREV_9300_20_OR_LATER(ah) ? true : false;
	ani->ofdmsTurn = true;
	ani->ofdmWeakSigDetect = true;
	ani->cckNoiseImmunityLevel = ATH9K_ANI_CCK_DEF_LEVEL;
	ani->ofdmNoiseImmunityLevel = ATH9K_ANI_OFDM_DEF_LEVEL;


	ah->aniperiod = ATH9K_ANI_PERIOD;
	ah->config.ani_poll_interval = ATH9K_ANI_POLLINTERVAL;

	ath9k_ani_restart(ah);
	ath9k_enable_mib_counters(ah);
}
