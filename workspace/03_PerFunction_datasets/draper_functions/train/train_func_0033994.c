ar9003_hw_init_cal(struct ath_hw *ah,
			       struct ath9k_channel *chan __unused)
{
	struct ath9k_hw_capabilities *pCap = &ah->caps;
	int val;
	int txiqcal_done = 0;

	val = REG_READ(ah, AR_ENT_OTP);
	DBG2("ath9k: ath9k: AR_ENT_OTP 0x%x\n", val);


	if (val & AR_ENT_OTP_CHAIN2_DISABLE)
		ar9003_hw_set_chain_masks(ah, 0x3, 0x3);
	else
		ar9003_hw_set_chain_masks(ah, pCap->rx_chainmask,
					  pCap->tx_chainmask);


	REG_RMW_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_1,
		      AR_PHY_TX_IQCAL_CONTROL_1_IQCORR_I_Q_COFF_DELPT,
		      DELPT);


	if (AR_SREV_9485_OR_LATER(ah))
		txiqcal_done = 1;
	else {
		txiqcal_done = ar9003_hw_tx_iq_cal_run(ah);
		REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_DIS);
		udelay(5);
		REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_EN);
	}


	REG_WRITE(ah, AR_PHY_AGC_CONTROL,
		  REG_READ(ah, AR_PHY_AGC_CONTROL) |
		  AR_PHY_AGC_CONTROL_CAL);


	if (!ath9k_hw_wait(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_CAL,
			   0, AH_WAIT_TIMEOUT)) {
		DBG("ath9k: "
			"offset calibration failed to complete in 1ms; noisy environment?\n");
		return 0;
	}

	if (txiqcal_done)
		ar9003_hw_tx_iq_cal_post_proc(ah);


	ar9003_hw_set_chain_masks(ah, ah->rxchainmask, ah->txchainmask);

	ath9k_hw_start_nfcal(ah, 1);


	ah->cal_list = ah->cal_list_last = ah->cal_list_curr = NULL;
	ah->supp_cals = IQ_MISMATCH_CAL;

	if (ah->supp_cals & IQ_MISMATCH_CAL) {
		INIT_CAL(&ah->iq_caldata);
		INSERT_CAL(ah, &ah->iq_caldata);
		DBG2("ath9k: "
			"enabling IQ Calibration.\n");
	}

	if (ah->supp_cals & TEMP_COMP_CAL) {
		INIT_CAL(&ah->tempCompCalData);
		INSERT_CAL(ah, &ah->tempCompCalData);
		DBG2("ath9k: "
			"enabling Temperature Compensation Calibration.\n");
	}


	ah->cal_list_curr = ah->cal_list;

	if (ah->cal_list_curr)
		ath9k_hw_reset_calibration(ah, ah->cal_list_curr);

	if (ah->caldata)
		ah->caldata->CalValid = 0;

	return 1;
}
