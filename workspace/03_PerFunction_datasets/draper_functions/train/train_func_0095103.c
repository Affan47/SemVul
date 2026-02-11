mwl8k_cmd_encryption_remove_key(struct ieee80211_hw *hw,
						struct ieee80211_vif *vif,
						u8 *addr,
						struct ieee80211_key_conf *key)
{
	struct mwl8k_cmd_set_key *cmd;
	int rc;
	struct mwl8k_vif *mwl8k_vif = MWL8K_VIF(vif);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	rc = mwl8k_encryption_set_cmd_info(cmd, addr, key);
	if (rc < 0)
		goto done;

	if (key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
			key->cipher == WLAN_CIPHER_SUITE_WEP104)
		mwl8k_vif->wep_key_conf[key->keyidx].enabled = 0;

	cmd->action = cpu_to_le32(MWL8K_ENCR_REMOVE_KEY);

	rc = mwl8k_post_pervif_cmd(hw, vif, &cmd->header);
done:
	kfree(cmd);

	return rc;
}
