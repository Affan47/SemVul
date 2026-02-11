iwl_init_scan_params(struct iwl_priv *priv)
{
	u8 ant_idx = fls(priv->nvm_data->valid_tx_ant) - 1;
	if (!priv->scan_tx_ant[IEEE80211_BAND_5GHZ])
		priv->scan_tx_ant[IEEE80211_BAND_5GHZ] = ant_idx;
	if (!priv->scan_tx_ant[IEEE80211_BAND_2GHZ])
		priv->scan_tx_ant[IEEE80211_BAND_2GHZ] = ant_idx;
}
