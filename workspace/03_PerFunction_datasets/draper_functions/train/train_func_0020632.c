ath9k_hw_updatetxtriglevel(struct ath_hw *ah, int bIncTrigLevel)
{
	u32 txcfg, curLevel, newLevel;

	if (ah->tx_trig_level >= ah->config.max_txtrig_level)
		return 0;

	ath9k_hw_disable_interrupts(ah);

	txcfg = REG_READ(ah, AR_TXCFG);
	curLevel = MS(txcfg, AR_FTRIG);
	newLevel = curLevel;
	if (bIncTrigLevel) {
		if (curLevel < ah->config.max_txtrig_level)
			newLevel++;
	} else if (curLevel > MIN_TX_FIFO_THRESHOLD)
		newLevel--;
	if (newLevel != curLevel)
		REG_WRITE(ah, AR_TXCFG,
			  (txcfg & ~AR_FTRIG) | SM(newLevel, AR_FTRIG));

	ath9k_hw_enable_interrupts(ah);

	ah->tx_trig_level = newLevel;

	return newLevel != curLevel;
}
