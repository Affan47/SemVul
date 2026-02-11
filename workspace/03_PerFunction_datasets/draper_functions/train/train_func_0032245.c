ath9k_set_power_sleep(struct ath_hw *ah, int setChip)
{
	REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);
	if (setChip) {


		REG_CLR_BIT(ah, AR_RTC_FORCE_WAKE,
			    AR_RTC_FORCE_WAKE_EN);
		if (!AR_SREV_9100(ah) && !AR_SREV_9300_20_OR_LATER(ah))
			REG_WRITE(ah, AR_RC, AR_RC_AHB | AR_RC_HOSTIF);


		if (!AR_SREV_5416(ah) && !AR_SREV_9271(ah))
			REG_CLR_BIT(ah, (AR_RTC_RESET),
				    AR_RTC_RESET_EN);
	}


	if (AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_WA,
			  ah->WARegVal & ~AR_WA_D3_L1_DISABLE);
}
