iwlagn_tx_cmd_build_rate(struct iwl_priv *priv,
				     struct iwl_tx_cmd *tx_cmd,
				     struct ieee80211_tx_info *info,
				     struct ieee80211_sta *sta,
				     __le16 fc)
{
	u32 rate_flags;
	int rate_idx;
	u8 rts_retry_limit;
	u8 data_retry_limit;
	u8 rate_plcp;

	if (priv->wowlan) {
		rts_retry_limit = IWLAGN_LOW_RETRY_LIMIT;
		data_retry_limit = IWLAGN_LOW_RETRY_LIMIT;
	} else {

		rts_retry_limit = IWLAGN_RTS_DFAULT_RETRY_LIMIT;


		if (ieee80211_is_probe_resp(fc)) {
			data_retry_limit = IWLAGN_MGMT_DFAULT_RETRY_LIMIT;
			rts_retry_limit =
				min(data_retry_limit, rts_retry_limit);
		} else if (ieee80211_is_back_req(fc))
			data_retry_limit = IWLAGN_BAR_DFAULT_RETRY_LIMIT;
		else
			data_retry_limit = IWLAGN_DEFAULT_TX_RETRY;
	}

	tx_cmd->data_retry_limit = data_retry_limit;
	tx_cmd->rts_retry_limit = rts_retry_limit;


	if (ieee80211_is_data(fc)) {
		tx_cmd->initial_rate_index = 0;
		tx_cmd->tx_flags |= TX_CMD_FLG_STA_RATE_MSK;
		return;
	} else if (ieee80211_is_back_req(fc))
		tx_cmd->tx_flags |= TX_CMD_FLG_STA_RATE_MSK;


	rate_idx = info->control.rates[0].idx;
	if (info->control.rates[0].flags & IEEE80211_TX_RC_MCS ||
			(rate_idx < 0) || (rate_idx > IWL_RATE_COUNT_LEGACY))
		rate_idx = rate_lowest_index(
				&priv->nvm_data->bands[info->band], sta);

	if (info->band == IEEE80211_BAND_5GHZ)
		rate_idx += IWL_FIRST_OFDM_RATE;

	rate_plcp = iwl_rates[rate_idx].plcp;

	rate_flags = 0;


	if ((rate_idx >= IWL_FIRST_CCK_RATE) && (rate_idx <= IWL_LAST_CCK_RATE))
		rate_flags |= RATE_MCS_CCK_MSK;


	if (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist &&
	    priv->bt_full_concurrent) {

		priv->mgmt_tx_ant = iwl_toggle_tx_ant(priv, priv->mgmt_tx_ant,
				first_antenna(priv->nvm_data->valid_tx_ant));
	} else
		priv->mgmt_tx_ant = iwl_toggle_tx_ant(
					priv, priv->mgmt_tx_ant,
					priv->nvm_data->valid_tx_ant);
	rate_flags |= iwl_ant_idx_to_flags(priv->mgmt_tx_ant);


	tx_cmd->rate_n_flags = iwl_hw_set_rate_n_flags(rate_plcp, rate_flags);
}
