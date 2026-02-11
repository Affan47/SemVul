rs_fill_lq_cmd(struct iwl_mvm *mvm,
			   struct ieee80211_sta *sta,
			   struct iwl_lq_sta *lq_sta,
			   const struct rs_rate *initial_rate)
{
	struct iwl_lq_cmd *lq_cmd = &lq_sta->lq;
	struct iwl_mvm_sta *mvmsta;
	struct iwl_mvm_vif *mvmvif;

	lq_cmd->agg_disable_start_th = IWL_MVM_RS_AGG_DISABLE_START;
	lq_cmd->agg_time_limit =
		cpu_to_le16(IWL_MVM_RS_AGG_TIME_LIMIT);

#ifdef CONFIG_MAC80211_DEBUGFS
	if (lq_sta->pers.dbg_fixed_rate) {
		rs_build_rates_table_from_fixed(mvm, lq_cmd,
						lq_sta->band,
						lq_sta->pers.dbg_fixed_rate);
		return;
	}
#endif
	if (WARN_ON_ONCE(!sta || !initial_rate))
		return;

	rs_build_rates_table(mvm, sta, lq_sta, initial_rate);

	if (fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_LQ_SS_PARAMS))
		rs_set_lq_ss_params(mvm, sta, lq_sta, initial_rate);

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	mvmvif = iwl_mvm_vif_from_mac80211(mvmsta->vif);

	if (num_of_ant(initial_rate->ant) == 1)
		lq_cmd->single_stream_ant_msk = initial_rate->ant;

	lq_cmd->agg_frame_cnt_limit = mvmsta->max_agg_bufsize;


	if (iwl_mvm_vif_low_latency(mvmvif)) {
		lq_cmd->agg_frame_cnt_limit--;

		if (mvm->low_latency_agg_frame_limit)
			lq_cmd->agg_frame_cnt_limit =
				min(lq_cmd->agg_frame_cnt_limit,
				    mvm->low_latency_agg_frame_limit);
	}

	if (mvmsta->vif->p2p)
		lq_cmd->flags |= LQ_FLAG_USE_RTS_MSK;

	lq_cmd->agg_time_limit =
			cpu_to_le16(iwl_mvm_coex_agg_time_limit(mvm, sta));
}
