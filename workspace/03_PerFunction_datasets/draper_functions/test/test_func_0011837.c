ath9k_hw_def_set_gain(struct ath_hw *ah,
				  struct modal_eep_header *pModal,
				  struct ar5416_eeprom_def *eep,
				  u8 txRxAttenLocal, int regChainOffset, int i)
{
	ENABLE_REG_RMW_BUFFER(ah);
	if (AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_3) {
		txRxAttenLocal = pModal->txRxAttenCh[i];

		if (AR_SREV_9280_20_OR_LATER(ah)) {
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN,
			      pModal->bswMargin[i]);
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_DB,
			      pModal->bswAtten[i]);
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN,
			      pModal->xatten2Margin[i]);
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN2_DB,
			      pModal->xatten2Db[i]);
		} else {
			REG_RMW(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
				SM(pModal-> bswMargin[i], AR_PHY_GAIN_2GHZ_BSW_MARGIN),
				AR_PHY_GAIN_2GHZ_BSW_MARGIN);
			REG_RMW(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
				SM(pModal->bswAtten[i], AR_PHY_GAIN_2GHZ_BSW_ATTEN),
				AR_PHY_GAIN_2GHZ_BSW_ATTEN);
		}
	}

	if (AR_SREV_9280_20_OR_LATER(ah)) {
		REG_RMW_FIELD(ah,
		      AR_PHY_RXGAIN + regChainOffset,
		      AR9280_PHY_RXGAIN_TXRX_ATTEN, txRxAttenLocal);
		REG_RMW_FIELD(ah,
		      AR_PHY_RXGAIN + regChainOffset,
		      AR9280_PHY_RXGAIN_TXRX_MARGIN, pModal->rxTxMarginCh[i]);
	} else {
		REG_RMW(ah, AR_PHY_RXGAIN + regChainOffset,
			SM(txRxAttenLocal, AR_PHY_RXGAIN_TXRX_ATTEN),
			AR_PHY_RXGAIN_TXRX_ATTEN);
		REG_RMW(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			SM(pModal->rxTxMarginCh[i], AR_PHY_GAIN_2GHZ_RXTX_MARGIN),
			AR_PHY_GAIN_2GHZ_RXTX_MARGIN);
	}
	REG_RMW_BUFFER_FLUSH(ah);
}
