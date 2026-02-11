il_send_rxon_timing(struct il_priv *il)
{
	u64 tsf;
	s32 interval_tm, rem;
	struct ieee80211_conf *conf = NULL;
	u16 beacon_int;
	struct ieee80211_vif *vif = il->vif;

	conf = &il->hw->conf;

	lockdep_assert_held(&il->mutex);

	memset(&il->timing, 0, sizeof(struct il_rxon_time_cmd));

	il->timing.timestamp = cpu_to_le64(il->timestamp);
	il->timing.listen_interval = cpu_to_le16(conf->listen_interval);

	beacon_int = vif ? vif->bss_conf.beacon_int : 0;


	il->timing.atim_win = 0;

	beacon_int =
	    il_adjust_beacon_interval(beacon_int,
				      il->hw_params.max_beacon_itrvl *
				      TIME_UNIT);
	il->timing.beacon_interval = cpu_to_le16(beacon_int);

	tsf = il->timestamp;
	interval_tm = beacon_int * TIME_UNIT;
	rem = do_div(tsf, interval_tm);
	il->timing.beacon_init_val = cpu_to_le32(interval_tm - rem);

	il->timing.dtim_period = vif ? (vif->bss_conf.dtim_period ? : 1) : 1;

	D_ASSOC("beacon interval %d beacon timer %d beacon tim %d\n",
		le16_to_cpu(il->timing.beacon_interval),
		le32_to_cpu(il->timing.beacon_init_val),
		le16_to_cpu(il->timing.atim_win));

	return il_send_cmd_pdu(il, C_RXON_TIMING, sizeof(il->timing),
			       &il->timing);
}
