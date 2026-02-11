mwifiex_ret_rf_tx_power(struct mwifiex_private *priv,
				   struct host_cmd_ds_command *resp)
{
	struct host_cmd_ds_rf_tx_pwr *txp = &resp->params.txp;
	u16 action = le16_to_cpu(txp->action);

	priv->tx_power_level = le16_to_cpu(txp->cur_level);

	if (action == HostCmd_ACT_GEN_GET) {
		priv->max_tx_power_level = txp->max_power;
		priv->min_tx_power_level = txp->min_power;
	}

	mwifiex_dbg(priv->adapter, INFO,
		    "Current TxPower Level=%d, Max Power=%d, Min Power=%d\n",
		    priv->tx_power_level, priv->max_tx_power_level,
		    priv->min_tx_power_level);

	return 0;
}
