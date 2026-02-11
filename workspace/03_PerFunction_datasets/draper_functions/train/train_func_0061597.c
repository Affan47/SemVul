ath9k_hw_4k_set_gain(struct ath_hw *ah,
				 struct modal_eep_4k_header *pModal,
				 struct ar5416_eeprom_4k *eep,
				 u8 txRxAttenLocal)
{
	ENABLE_REG_RMW_BUFFER(ah);
	REG_RMW(ah, AR_PHY_SWITCH_CHAIN_0,
		pModal->antCtrlChain[0], 0);

	REG_RMW(ah, AR_PHY_TIMING_CTRL4(0),
		SM(pModal->iqCalICh[0], AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF) |
		SM(pModal->iqCalQCh[0], AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF),
		AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF | AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF);

	if ((eep->baseEepHeader.version & AR5416_EEP_VER_MINOR_MASK) >=
	    AR5416_EEP_MINOR_VER_3) {
		txRxAttenLocal = pModal->txRxAttenCh[0];

		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ,
			      AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN, pModal->bswMargin[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ,
			      AR_PHY_GAIN_2GHZ_XATTEN1_DB, pModal->bswAtten[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ,
			      AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN,
			      pModal->xatten2Margin[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ,
			      AR_PHY_GAIN_2GHZ_XATTEN2_DB, pModal->xatten2Db[0]);


		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + 0x1000,
			      AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN,
			      pModal->bswMargin[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + 0x1000,
			      AR_PHY_GAIN_2GHZ_XATTEN1_DB, pModal->bswAtten[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + 0x1000,
			      AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN,
			      pModal->xatten2Margin[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + 0x1000,
			      AR_PHY_GAIN_2GHZ_XATTEN2_DB,
			      pModal->xatten2Db[0]);
	}

	REG_RMW_FIELD(ah, AR_PHY_RXGAIN,
		      AR9280_PHY_RXGAIN_TXRX_ATTEN, txRxAttenLocal);
	REG_RMW_FIELD(ah, AR_PHY_RXGAIN,
		      AR9280_PHY_RXGAIN_TXRX_MARGIN, pModal->rxTxMarginCh[0]);

	REG_RMW_FIELD(ah, AR_PHY_RXGAIN + 0x1000,
		      AR9280_PHY_RXGAIN_TXRX_ATTEN, txRxAttenLocal);
	REG_RMW_FIELD(ah, AR_PHY_RXGAIN + 0x1000,
		      AR9280_PHY_RXGAIN_TXRX_MARGIN, pModal->rxTxMarginCh[0]);
	REG_RMW_BUFFER_FLUSH(ah);
}
