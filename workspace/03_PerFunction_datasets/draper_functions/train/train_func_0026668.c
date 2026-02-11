ar9003_hw_xlna_bias_strength_apply(struct ath_hw *ah, bool is2ghz)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	u8 bias;

	if (!(eep->baseEepHeader.miscConfiguration & 0x40))
		return;

	if (!AR_SREV_9300(ah))
		return;

	bias = ar9003_modal_header(ah, is2ghz)->xlna_bias_strength;
	REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_RXTX4, AR_PHY_65NM_RXTX4_XLNA_BIAS,
		      bias & 0x3);
	bias >>= 2;
	REG_RMW_FIELD(ah, AR_PHY_65NM_CH1_RXTX4, AR_PHY_65NM_RXTX4_XLNA_BIAS,
		      bias & 0x3);
	bias >>= 2;
	REG_RMW_FIELD(ah, AR_PHY_65NM_CH2_RXTX4, AR_PHY_65NM_RXTX4_XLNA_BIAS,
		      bias & 0x3);
}
