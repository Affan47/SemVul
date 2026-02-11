mwl8k_cmd_update_stadb_add(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct ieee80211_sta *sta)
{
	struct mwl8k_cmd_update_stadb *cmd;
	struct peer_capability_info *p;
	u32 rates;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_UPDATE_STADB);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le32(MWL8K_STA_DB_MODIFY_ENTRY);
	memcpy(cmd->peer_addr, sta->addr, ETH_ALEN);

	p = &cmd->peer_info;
	p->peer_type = MWL8K_PEER_TYPE_ACCESSPOINT;
	p->basic_caps = cpu_to_le16(vif->bss_conf.assoc_capability);
	p->ht_support = sta->ht_cap.ht_supported;
	p->ht_caps = cpu_to_le16(sta->ht_cap.cap);
	p->extended_ht_caps = (sta->ht_cap.ampdu_factor & 3) |
		((sta->ht_cap.ampdu_density & 7) << 2);
	if (hw->conf.chandef.chan->band == IEEE80211_BAND_2GHZ)
		rates = sta->supp_rates[IEEE80211_BAND_2GHZ];
	else
		rates = sta->supp_rates[IEEE80211_BAND_5GHZ] << 5;
	legacy_rate_mask_to_array(p->legacy_rates, rates);
	memcpy(p->ht_rates, sta->ht_cap.mcs.rx_mask, 16);
	p->interop = 1;
	p->amsdu_enabled = 0;

	rc = mwl8k_post_cmd(hw, &cmd->header);
	if (!rc)
		rc = p->station_id;
	kfree(cmd);

	return rc;
}
