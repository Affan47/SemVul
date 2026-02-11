ipw2100_set_rts_threshold(struct ipw2100_priv *priv, u32 threshold)
{
	struct host_command cmd = {
		.host_command = RTS_THRESHOLD,
		.host_command_sequence = 0,
		.host_command_length = 4
	};
	int err;

	if (threshold & RTS_DISABLED)
		cmd.host_command_parameters[0] = MAX_RTS_THRESHOLD;
	else
		cmd.host_command_parameters[0] = threshold & ~RTS_DISABLED;

	err = ipw2100_hw_send_command(priv, &cmd);
	if (err)
		return err;

	priv->rts_threshold = threshold;

	return 0;
}
