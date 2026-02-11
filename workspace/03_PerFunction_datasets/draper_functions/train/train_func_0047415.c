ath9k_hw_set_global_txtimeout(struct ath_hw *ah, u32 tu)
{
	if (tu > 0xFFFF) {
		DBG("ath9k: "
			"bad global tx timeout %d\n", tu);
		ah->globaltxtimeout = (u32) -1;
		return 0;
	} else {
		REG_RMW_FIELD(ah, AR_GTXTO, AR_GTXTO_TIMEOUT_LIMIT, tu);
		ah->globaltxtimeout = tu;
		return 1;
	}
}
