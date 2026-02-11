ath9k_hw_set_dma(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	ENABLE_REGWRITE_BUFFER(ah);


	if (!AR_SREV_9300_20_OR_LATER(ah))
		REG_SET_BIT(ah, AR_AHB_MODE, AR_AHB_PREFETCH_RD_EN);


	REG_RMW(ah, AR_TXCFG, AR_TXCFG_DMASZ_128B, AR_TXCFG_DMASZ_MASK);

	REGWRITE_BUFFER_FLUSH(ah);


	if (!AR_SREV_9300_20_OR_LATER(ah))
		REG_RMW_FIELD(ah, AR_TXCFG, AR_FTRIG, ah->tx_trig_level);

	ENABLE_REGWRITE_BUFFER(ah);


	REG_RMW(ah, AR_RXCFG, AR_RXCFG_DMASZ_128B, AR_RXCFG_DMASZ_MASK);


	REG_WRITE(ah, AR_RXFIFO_CFG, 0x200);

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		REG_RMW_FIELD(ah, AR_RXBP_THRESH, AR_RXBP_THRESH_HP, 0x1);
		REG_RMW_FIELD(ah, AR_RXBP_THRESH, AR_RXBP_THRESH_LP, 0x1);

		ath9k_hw_set_rx_bufsize(ah, common->rx_bufsize -
			ah->caps.rx_status_len);
	}


	if (AR_SREV_9285(ah)) {


		REG_WRITE(ah, AR_PCU_TXBUF_CTRL,
			  AR_9285_PCU_TXBUF_CTRL_USABLE_SIZE);
	} else if (!AR_SREV_9271(ah)) {
		REG_WRITE(ah, AR_PCU_TXBUF_CTRL,
			  AR_PCU_TXBUF_CTRL_USABLE_SIZE);
	}

	REGWRITE_BUFFER_FLUSH(ah);

	if (AR_SREV_9300_20_OR_LATER(ah))
		ath9k_hw_reset_txstatus_ring(ah);
}
