ath5k_txq_release(struct ath5k_hw *ah)
{
	struct ath5k_txq *txq = ah->txqs;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(ah->txqs); i++, txq++)
		if (txq->setup) {
			ath5k_hw_release_tx_queue(ah, txq->qnum);
			txq->setup = false;
		}
}
