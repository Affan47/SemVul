atmel_send_command(struct atmel_private *priv, int command,
			       void *cmd, int cmd_size)
{
	if (cmd)
		atmel_copy_to_card(priv->dev, atmel_co(priv, CMD_BLOCK_PARAMETERS_OFFSET),
				   cmd, cmd_size);

	atmel_wmem8(priv, atmel_co(priv, CMD_BLOCK_COMMAND_OFFSET), command);
	atmel_wmem8(priv, atmel_co(priv, CMD_BLOCK_STATUS_OFFSET), 0);
}
