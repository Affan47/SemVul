ath9k_htc_choose_bslot(struct ath9k_htc_priv *priv,
				  struct wmi_event_swba *swba)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	u64 tsf;
	u32 tsftu;
	u16 intval;
	int slot;

	intval = priv->cur_beacon_conf.beacon_interval;

	tsf = be64_to_cpu(swba->tsf);
	tsftu = TSF_TO_TU(tsf >> 32, tsf);
	slot = ((tsftu % intval) * ATH9K_HTC_MAX_BCN_VIF) / intval;
	slot = ATH9K_HTC_MAX_BCN_VIF - slot - 1;

	ath_dbg(common, BEACON,
		"Choose slot: %d, tsf: %llu, tsftu: %u, intval: %u\n",
		slot, tsf, tsftu, intval);

	return slot;
}
