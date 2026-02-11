__lbs_mesh_config_send(struct lbs_private *priv,
				  struct cmd_ds_mesh_config *cmd,
				  uint16_t action, uint16_t type)
{
	int ret;
	u16 command = CMD_MESH_CONFIG_OLD;

	lbs_deb_enter(LBS_DEB_CMD);


	if (priv->mesh_tlv == TLV_TYPE_MESH_ID)
		command = CMD_MESH_CONFIG |
			  (MESH_IFACE_ID << MESH_IFACE_BIT_OFFSET);

	cmd->hdr.command = cpu_to_le16(command);
	cmd->hdr.size = cpu_to_le16(sizeof(struct cmd_ds_mesh_config));
	cmd->hdr.result = 0;

	cmd->type = cpu_to_le16(type);
	cmd->action = cpu_to_le16(action);

	ret = lbs_cmd_with_response(priv, command, cmd);

	lbs_deb_leave(LBS_DEB_CMD);
	return ret;
}
