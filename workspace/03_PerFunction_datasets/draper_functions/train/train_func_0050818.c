iwlagn_send_advance_bt_config(struct iwl_priv *priv)
{
	struct iwl_basic_bt_cmd basic = {
		.max_kill = IWLAGN_BT_MAX_KILL_DEFAULT,
		.bt3_timer_t7_value = IWLAGN_BT3_T7_DEFAULT,
		.bt3_prio_sample_time = IWLAGN_BT3_PRIO_SAMPLE_DEFAULT,
		.bt3_timer_t2_value = IWLAGN_BT3_T2_DEFAULT,
	};
	struct iwl_bt_cmd_v1 bt_cmd_v1;
	struct iwl_bt_cmd_v2 bt_cmd_v2;
	int ret;

	BUILD_BUG_ON(sizeof(iwlagn_def_3w_lookup) !=
			sizeof(basic.bt3_lookup_table));

	if (priv->lib->bt_params) {


		if (priv->lib->bt_params->bt_session_2) {
			bt_cmd_v2.prio_boost = cpu_to_le32(
				priv->lib->bt_params->bt_prio_boost);
			bt_cmd_v2.tx_prio_boost = 0;
			bt_cmd_v2.rx_prio_boost = 0;
		} else {

			WARN_ON(priv->lib->bt_params->bt_prio_boost & ~0xFF);
			bt_cmd_v1.prio_boost =
				priv->lib->bt_params->bt_prio_boost;
			bt_cmd_v1.tx_prio_boost = 0;
			bt_cmd_v1.rx_prio_boost = 0;
		}
	} else {
		IWL_ERR(priv, "failed to construct BT Coex Config\n");
		return;
	}


	basic.kill_ack_mask = priv->kill_ack_mask;
	basic.kill_cts_mask = priv->kill_cts_mask;
	if (priv->reduced_txpower)
		basic.reduce_txpower = IWLAGN_BT_REDUCED_TX_PWR;
	basic.valid = priv->bt_valid;


	if (!iwlwifi_mod_params.bt_coex_active ||
	    priv->iw_mode == NL80211_IFTYPE_ADHOC) {
		basic.flags = IWLAGN_BT_FLAG_COEX_MODE_DISABLED;
	} else {
		basic.flags = IWLAGN_BT_FLAG_COEX_MODE_3W <<
					IWLAGN_BT_FLAG_COEX_MODE_SHIFT;

		if (!priv->bt_enable_pspoll)
			basic.flags |= IWLAGN_BT_FLAG_SYNC_2_BT_DISABLE;
		else
			basic.flags &= ~IWLAGN_BT_FLAG_SYNC_2_BT_DISABLE;

		if (priv->bt_ch_announce)
			basic.flags |= IWLAGN_BT_FLAG_CHANNEL_INHIBITION;
		IWL_DEBUG_COEX(priv, "BT coex flag: 0X%x\n", basic.flags);
	}
	priv->bt_enable_flag = basic.flags;
	if (priv->bt_full_concurrent)
		memcpy(basic.bt3_lookup_table, iwlagn_concurrent_lookup,
			sizeof(iwlagn_concurrent_lookup));
	else
		memcpy(basic.bt3_lookup_table, iwlagn_def_3w_lookup,
			sizeof(iwlagn_def_3w_lookup));

	IWL_DEBUG_COEX(priv, "BT coex %s in %s mode\n",
		       basic.flags ? "active" : "disabled",
		       priv->bt_full_concurrent ?
		       "full concurrency" : "3-wire");

	if (priv->lib->bt_params->bt_session_2) {
		memcpy(&bt_cmd_v2.basic, &basic,
			sizeof(basic));
		ret = iwl_dvm_send_cmd_pdu(priv, REPLY_BT_CONFIG,
			0, sizeof(bt_cmd_v2), &bt_cmd_v2);
	} else {
		memcpy(&bt_cmd_v1.basic, &basic,
			sizeof(basic));
		ret = iwl_dvm_send_cmd_pdu(priv, REPLY_BT_CONFIG,
			0, sizeof(bt_cmd_v1), &bt_cmd_v1);
	}
	if (ret)
		IWL_ERR(priv, "failed to send BT Coex Config\n");

}
