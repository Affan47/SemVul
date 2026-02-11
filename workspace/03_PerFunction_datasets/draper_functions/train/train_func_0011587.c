ath9k_hw_ani_read_counters(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ar5416AniState *aniState = &ah->curchan->ani;
	u32 ofdm_base = 0;
	u32 cck_base = 0;
	u32 ofdmPhyErrCnt, cckPhyErrCnt;
	u32 phyCnt1, phyCnt2;
	int32_t listenTime;

	ath_hw_cycle_counters_update(common);
	listenTime = ath_hw_get_listen_time(common);

	if (listenTime <= 0) {
		ah->stats.ast_ani_lneg++;
		ath9k_ani_restart(ah);
		return 0;
	}

	if (!use_new_ani(ah)) {
		ofdm_base = AR_PHY_COUNTMAX - ah->config.ofdm_trig_high;
		cck_base = AR_PHY_COUNTMAX - ah->config.cck_trig_high;
	}

	aniState->listenTime += listenTime;

	phyCnt1 = REG_READ(ah, AR_PHY_ERR_1);
	phyCnt2 = REG_READ(ah, AR_PHY_ERR_2);

	if (!use_new_ani(ah) && (phyCnt1 < ofdm_base || phyCnt2 < cck_base)) {
		if (phyCnt1 < ofdm_base) {
			DBG2("ath9k: "
				"phyCnt1 0x%x, resetting counter value to 0x%x\n",
				phyCnt1, ofdm_base);
			REG_WRITE(ah, AR_PHY_ERR_1, ofdm_base);
			REG_WRITE(ah, AR_PHY_ERR_MASK_1,
				  AR_PHY_ERR_OFDM_TIMING);
		}
		if (phyCnt2 < cck_base) {
			DBG2("ath9k: "
				"phyCnt2 0x%x, resetting counter value to 0x%x\n",
				phyCnt2, cck_base);
			REG_WRITE(ah, AR_PHY_ERR_2, cck_base);
			REG_WRITE(ah, AR_PHY_ERR_MASK_2,
				  AR_PHY_ERR_CCK_TIMING);
		}
		return 0;
	}

	ofdmPhyErrCnt = phyCnt1 - ofdm_base;
	ah->stats.ast_ani_ofdmerrs +=
		ofdmPhyErrCnt - aniState->ofdmPhyErrCount;
	aniState->ofdmPhyErrCount = ofdmPhyErrCnt;

	cckPhyErrCnt = phyCnt2 - cck_base;
	ah->stats.ast_ani_cckerrs +=
		cckPhyErrCnt - aniState->cckPhyErrCount;
	aniState->cckPhyErrCount = cckPhyErrCnt;
	return 1;
}
