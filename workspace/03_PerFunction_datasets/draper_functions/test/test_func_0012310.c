ath5k_hw_start_tx_dma(struct ath5k_hw *ah, unsigned int queue)
{
	u32 tx_queue;

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);


	if (ah->ah_txq[queue].tqi_type == AR5K_TX_QUEUE_INACTIVE)
		return -EINVAL;

	if (ah->ah_version == AR5K_AR5210) {
		tx_queue = ath5k_hw_reg_read(ah, AR5K_CR);


		switch (ah->ah_txq[queue].tqi_type) {
		case AR5K_TX_QUEUE_DATA:
			tx_queue |= AR5K_CR_TXE0 & ~AR5K_CR_TXD0;
			break;
		case AR5K_TX_QUEUE_BEACON:
			tx_queue |= AR5K_CR_TXE1 & ~AR5K_CR_TXD1;
			ath5k_hw_reg_write(ah, AR5K_BCR_TQ1V | AR5K_BCR_BDMAE,
					AR5K_BSR);
			break;
		case AR5K_TX_QUEUE_CAB:
			tx_queue |= AR5K_CR_TXE1 & ~AR5K_CR_TXD1;
			ath5k_hw_reg_write(ah, AR5K_BCR_TQ1FV | AR5K_BCR_TQ1V |
				AR5K_BCR_BDMAE, AR5K_BSR);
			break;
		default:
			return -EINVAL;
		}

		ath5k_hw_reg_write(ah, tx_queue, AR5K_CR);
		ath5k_hw_reg_read(ah, AR5K_CR);
	} else {

		if (AR5K_REG_READ_Q(ah, AR5K_QCU_TXD, queue))
			return -EIO;


		AR5K_REG_WRITE_Q(ah, AR5K_QCU_TXE, queue);
	}

	return 0;
}
