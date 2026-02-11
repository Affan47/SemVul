ath9k_hw_reset_txstatus_ring(struct ath_hw *ah)
{
	ah->ts_tail = 0;

	memset((void *) ah->ts_ring, 0,
		ah->ts_size * sizeof(struct ar9003_txs));

	ath_dbg(ath9k_hw_common(ah), XMIT,
		"TS Start 0x%x End 0x%x Virt %p, Size %d\n",
		ah->ts_paddr_start, ah->ts_paddr_end,
		ah->ts_ring, ah->ts_size);

	REG_WRITE(ah, AR_Q_STATUS_RING_START, ah->ts_paddr_start);
	REG_WRITE(ah, AR_Q_STATUS_RING_END, ah->ts_paddr_end);
}
