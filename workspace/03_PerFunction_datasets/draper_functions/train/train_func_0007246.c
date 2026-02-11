mwifiex_ret_802_11_hs_cfg(struct mwifiex_private *priv,
			      struct host_cmd_ds_command *resp)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct host_cmd_ds_802_11_hs_cfg_enh *phs_cfg =
		&resp->params.opt_hs_cfg;
	uint32_t conditions = le32_to_cpu(phs_cfg->params.hs_config.conditions);

	if (phs_cfg->action == cpu_to_le16(HS_ACTIVATE) &&
	    adapter->iface_type != MWIFIEX_USB) {
		mwifiex_hs_activated_event(priv, true);
		return 0;
	} else {
		mwifiex_dbg(adapter, CMD,
			    "cmd: CMD_RESP: HS_CFG cmd reply\t"
			    " result=%#x, conditions=0x%x gpio=0x%x gap=0x%x\n",
			    resp->result, conditions,
			    phs_cfg->params.hs_config.gpio,
			    phs_cfg->params.hs_config.gap);
	}
	if (conditions != HS_CFG_CANCEL) {
		adapter->is_hs_configured = true;
		if (adapter->iface_type == MWIFIEX_USB)
			mwifiex_hs_activated_event(priv, true);
	} else {
		adapter->is_hs_configured = false;
		if (adapter->hs_activated)
			mwifiex_hs_activated_event(priv, false);
	}

	return 0;
}
