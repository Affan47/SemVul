mwifiex_cmd_rf_antenna(struct mwifiex_private *priv,
				  struct host_cmd_ds_command *cmd,
				  u16 cmd_action,
				  struct mwifiex_ds_ant_cfg *ant_cfg)
{
	struct host_cmd_ds_rf_ant_mimo *ant_mimo = &cmd->params.ant_mimo;
	struct host_cmd_ds_rf_ant_siso *ant_siso = &cmd->params.ant_siso;

	cmd->command = cpu_to_le16(HostCmd_CMD_RF_ANTENNA);

	if (cmd_action != HostCmd_ACT_GEN_SET)
		return 0;

	if (priv->adapter->hw_dev_mcs_support == HT_STREAM_2X2) {
		cmd->size = cpu_to_le16(sizeof(struct host_cmd_ds_rf_ant_mimo) +
					S_DS_GEN);
		ant_mimo->action_tx = cpu_to_le16(HostCmd_ACT_SET_TX);
		ant_mimo->tx_ant_mode = cpu_to_le16((u16)ant_cfg->tx_ant);
		ant_mimo->action_rx = cpu_to_le16(HostCmd_ACT_SET_RX);
		ant_mimo->rx_ant_mode = cpu_to_le16((u16)ant_cfg->rx_ant);
	} else {
		cmd->size = cpu_to_le16(sizeof(struct host_cmd_ds_rf_ant_siso) +
					S_DS_GEN);
		ant_siso->action = cpu_to_le16(HostCmd_ACT_SET_BOTH);
		ant_siso->ant_mode = cpu_to_le16((u16)ant_cfg->tx_ant);
	}

	return 0;
}
