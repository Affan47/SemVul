ath5k_hw_start_tx_dma(struct ath5k_hw *ah, unsigned int queue)
{
	u32 tx_queue;


	if (ah->ah_txq.tqi_type == AR5K_TX_QUEUE_INACTIVE)
		return -EIO;

	if (ah->ah_version == AR5K_AR5210) {
		tx_queue = ath5k_hw_reg_read(ah, AR5K_CR);


		tx_queue |= AR5K_CR_TXE0 & ~AR5K_CR_TXD0;


		ath5k_hw_reg_write(ah, tx_queue, AR5K_CR);
		ath5k_hw_reg_read(ah, AR5K_CR);
	} else {

		if (AR5K_REG_READ_Q(ah, AR5K_QCU_TXD, queue))
			return -EIO;


		AR5K_REG_WRITE_Q(ah, AR5K_QCU_TXE, queue);
	}

	return 0;
}
