ar9003_hw_xpa_timing_control_apply(struct ath_hw *ah, bool is2ghz)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	u8 xpa_ctl;

	if (!(eep->baseEepHeader.featureEnable & 0x80))
		return;

	if (!AR_SREV_9300(ah) &&
	    !AR_SREV_9340(ah) &&
	    !AR_SREV_9580(ah) &&
	    !AR_SREV_9531(ah) &&
	    !AR_SREV_9561(ah))
		return;

	xpa_ctl = ar9003_modal_header(ah, is2ghz)->txFrameToXpaOn;
	if (is2ghz)
		REG_RMW_FIELD(ah, AR_PHY_XPA_TIMING_CTL,
			      AR_PHY_XPA_TIMING_CTL_FRAME_XPAB_ON, xpa_ctl);
	else
		REG_RMW_FIELD(ah, AR_PHY_XPA_TIMING_CTL,
			      AR_PHY_XPA_TIMING_CTL_FRAME_XPAA_ON, xpa_ctl);
}
