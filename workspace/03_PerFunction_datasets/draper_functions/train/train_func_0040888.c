iwlagn_update_qos(struct iwl_priv *priv,
			      struct iwl_rxon_context *ctx)
{
	int ret;

	if (!ctx->is_active)
		return;

	ctx->qos_data.def_qos_parm.qos_flags = 0;

	if (ctx->qos_data.qos_active)
		ctx->qos_data.def_qos_parm.qos_flags |=
			QOS_PARAM_FLG_UPDATE_EDCA_MSK;

	if (ctx->ht.enabled)
		ctx->qos_data.def_qos_parm.qos_flags |= QOS_PARAM_FLG_TGN_MSK;

	IWL_DEBUG_INFO(priv, "send QoS cmd with Qos active=%d FLAGS=0x%X\n",
		      ctx->qos_data.qos_active,
		      ctx->qos_data.def_qos_parm.qos_flags);

	ret = iwl_dvm_send_cmd_pdu(priv, ctx->qos_cmd, 0,
			       sizeof(struct iwl_qosparam_cmd),
			       &ctx->qos_data.def_qos_parm);
	if (ret)
		IWL_DEBUG_QUIET_RFKILL(priv, "Failed to update QoS\n");
}
