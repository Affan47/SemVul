rs_get_rate(void *mvm_r, struct ieee80211_sta *sta, void *mvm_sta,
			struct ieee80211_tx_rate_control *txrc)
{
	struct sk_buff *skb = txrc->skb;
	struct iwl_op_mode *op_mode __maybe_unused =
			(struct iwl_op_mode *)mvm_r;
	struct iwl_mvm *mvm __maybe_unused = IWL_OP_MODE_GET_MVM(op_mode);
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct iwl_lq_sta *lq_sta = mvm_sta;
	struct rs_rate *optimal_rate;
	u32 last_ucode_rate;

	if (sta && !iwl_mvm_sta_from_mac80211(sta)->vif) {


		sta = NULL;
		mvm_sta = NULL;
	}


	if (lq_sta && !lq_sta->pers.drv) {
		IWL_DEBUG_RATE(mvm, "Rate scaling not initialized yet.\n");
		mvm_sta = NULL;
	}


	if (rate_control_send_low(sta, mvm_sta, txrc))
		return;

	iwl_mvm_hwrate_to_tx_rate(lq_sta->last_rate_n_flags,
				  info->band, &info->control.rates[0]);
	info->control.rates[0].count = 1;


	if (lq_sta->rs_state != RS_STATE_STAY_IN_COLUMN) {
		optimal_rate = rs_get_optimal_rate(mvm, lq_sta);
		last_ucode_rate = ucode_rate_from_rs_rate(mvm,
							  optimal_rate);
		iwl_mvm_hwrate_to_tx_rate(last_ucode_rate, info->band,
					  &txrc->reported_rate);
	}
}
