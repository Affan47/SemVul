ar9003_hw_do_pcoem_manual_peak_cal(struct ath_hw *ah,
					       struct ath9k_channel *chan,
					       bool run_rtt_cal)
{
	struct ath9k_hw_cal_data *caldata = ah->caldata;
	int i;

	if (!AR_SREV_9462(ah) && !AR_SREV_9565(ah) && !AR_SREV_9485(ah))
		return;

	if ((ah->caps.hw_caps & ATH9K_HW_CAP_RTT) && !run_rtt_cal)
		return;

	for (i = 0; i < AR9300_MAX_CHAINS; i++) {
		if (!(ah->rxchainmask & (1 << i)))
			continue;
		ar9003_hw_manual_peak_cal(ah, i, IS_CHAN_2GHZ(chan));
	}

	if (caldata)
		set_bit(SW_PKDET_DONE, &caldata->cal_flags);

	if ((ah->caps.hw_caps & ATH9K_HW_CAP_RTT) && caldata) {
		if (IS_CHAN_2GHZ(chan)){
			caldata->caldac[0] = REG_READ_FIELD(ah,
						    AR_PHY_65NM_RXRF_AGC(0),
						    AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR);
			caldata->caldac[1] = REG_READ_FIELD(ah,
						    AR_PHY_65NM_RXRF_AGC(1),
						    AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR);
		} else {
			caldata->caldac[0] = REG_READ_FIELD(ah,
						    AR_PHY_65NM_RXRF_AGC(0),
						    AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR);
			caldata->caldac[1] = REG_READ_FIELD(ah,
						    AR_PHY_65NM_RXRF_AGC(1),
						    AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR);
		}
	}
}
