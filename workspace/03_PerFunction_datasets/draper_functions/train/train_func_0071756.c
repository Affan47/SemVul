lbs_set_key_material(struct lbs_private *priv,
				int key_type, int key_info,
				const u8 *key, u16 key_len)
{
	struct cmd_key_material cmd;
	int ret;

	lbs_deb_enter(LBS_DEB_CFG80211);


	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.param.type = cpu_to_le16(TLV_TYPE_KEY_MATERIAL);
	cmd.param.length = cpu_to_le16(sizeof(cmd.param) - 4);
	cmd.param.keytypeid = cpu_to_le16(key_type);
	cmd.param.keyinfo = cpu_to_le16(key_info);
	cmd.param.keylen = cpu_to_le16(key_len);
	if (key && key_len)
		memcpy(cmd.param.key, key, key_len);

	ret = lbs_cmd_with_response(priv, CMD_802_11_KEY_MATERIAL, &cmd);

	lbs_deb_leave(LBS_DEB_CFG80211);
	return ret;
}
