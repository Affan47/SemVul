iwl_mvm_bt_coex_notif_handle(struct iwl_mvm *mvm)
{
	struct iwl_bt_iterator_data data = {
		.mvm = mvm,
		.notif = &mvm->last_bt_notif_old,
	};
	struct iwl_bt_coex_ci_cmd_old cmd = {};
	u8 ci_bw_idx;


	if (unlikely(mvm->bt_force_ant_mode != BT_FORCE_ANT_DIS))
		return;

	rcu_read_lock();
	ieee80211_iterate_active_interfaces_atomic(
					mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_bt_notif_iterator, &data);

	if (data.primary) {
		struct ieee80211_chanctx_conf *chan = data.primary;

		if (WARN_ON(!chan->def.chan)) {
			rcu_read_unlock();
			return;
		}

		if (chan->def.width < NL80211_CHAN_WIDTH_40) {
			ci_bw_idx = 0;
			cmd.co_run_bw_primary = 0;
		} else {
			cmd.co_run_bw_primary = 1;
			if (chan->def.center_freq1 >
			    chan->def.chan->center_freq)
				ci_bw_idx = 2;
			else
				ci_bw_idx = 1;
		}

		cmd.bt_primary_ci =
			iwl_ci_mask[chan->def.chan->hw_value][ci_bw_idx];
		cmd.primary_ch_phy_id = *((u16 *)data.primary->drv_priv);
	}

	if (data.secondary) {
		struct ieee80211_chanctx_conf *chan = data.secondary;

		if (WARN_ON(!data.secondary->def.chan)) {
			rcu_read_unlock();
			return;
		}

		if (chan->def.width < NL80211_CHAN_WIDTH_40) {
			ci_bw_idx = 0;
			cmd.co_run_bw_secondary = 0;
		} else {
			cmd.co_run_bw_secondary = 1;
			if (chan->def.center_freq1 >
			    chan->def.chan->center_freq)
				ci_bw_idx = 2;
			else
				ci_bw_idx = 1;
		}

		cmd.bt_secondary_ci =
			iwl_ci_mask[chan->def.chan->hw_value][ci_bw_idx];
		cmd.secondary_ch_phy_id = *((u16 *)data.secondary->drv_priv);
	}

	rcu_read_unlock();


	if (memcmp(&cmd, &mvm->last_bt_ci_cmd_old, sizeof(cmd))) {
		if (iwl_mvm_send_cmd_pdu(mvm, BT_COEX_CI, 0,
					 sizeof(cmd), &cmd))
			IWL_ERR(mvm, "Failed to send BT_CI cmd\n");
		memcpy(&mvm->last_bt_ci_cmd_old, &cmd, sizeof(cmd));
	}

	if (iwl_mvm_bt_udpate_ctrl_kill_msk(mvm))
		IWL_ERR(mvm, "Failed to update the ctrl_kill_msk\n");
}
