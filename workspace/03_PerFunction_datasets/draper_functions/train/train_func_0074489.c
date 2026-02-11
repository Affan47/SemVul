ath9k_hw_setslottime(struct ath_hw *ah, u32 us)
{
	u32 val = ath9k_hw_mac_to_clks(ah, us);
	val = min(val, (u32) 0xFFFF);
	REG_WRITE(ah, AR_D_GBL_IFS_SLOT, val);
}
