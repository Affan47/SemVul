ar9003_hw_bb_watchdog_dbg_info(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 status;

	if (likely(!(common->debug_mask & ATH_DBG_RESET)))
		return;

	status = ah->bb_watchdog_last_status;
	ath_dbg(common, RESET,
		"\n==== BB update: BB status=0x%08x ====\n", status);
	ath_dbg(common, RESET,
		"** BB state: wd=%u det=%u rdar=%u rOFDM=%d rCCK=%u tOFDM=%u tCCK=%u agc=%u src=%u **\n",
		MS(status, AR_PHY_WATCHDOG_INFO),
		MS(status, AR_PHY_WATCHDOG_DET_HANG),
		MS(status, AR_PHY_WATCHDOG_RADAR_SM),
		MS(status, AR_PHY_WATCHDOG_RX_OFDM_SM),
		MS(status, AR_PHY_WATCHDOG_RX_CCK_SM),
		MS(status, AR_PHY_WATCHDOG_TX_OFDM_SM),
		MS(status, AR_PHY_WATCHDOG_TX_CCK_SM),
		MS(status, AR_PHY_WATCHDOG_AGC_SM),
		MS(status, AR_PHY_WATCHDOG_SRCH_SM));

	ath_dbg(common, RESET, "** BB WD cntl: cntl1=0x%08x cntl2=0x%08x **\n",
		REG_READ(ah, AR_PHY_WATCHDOG_CTL_1),
		REG_READ(ah, AR_PHY_WATCHDOG_CTL_2));
	ath_dbg(common, RESET, "** BB mode: BB_gen_controls=0x%08x **\n",
		REG_READ(ah, AR_PHY_GEN_CTRL));

#define PCT(_field) (common->cc_survey._field * 100 / common->cc_survey.cycles)
	if (common->cc_survey.cycles)
		ath_dbg(common, RESET,
			"** BB busy times: rx_clear=%d%%, rx_frame=%d%%, tx_frame=%d%% **\n",
			PCT(rx_busy), PCT(rx_frame), PCT(tx_frame));

	ath_dbg(common, RESET, "==== BB update: done ====\n\n");
}
