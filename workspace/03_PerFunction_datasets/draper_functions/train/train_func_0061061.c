mlx4_SET_PORT_fcs_check(struct mlx4_dev *dev, u8 port, u8 ignore_fcs_value)
{
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_set_port_general_context *context;
	u32 in_mod;
	int err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	context = mailbox->buf;
	context->v_ignore_fcs |= MLX4_FLAG_V_IGNORE_FCS_MASK;
	if (ignore_fcs_value)
		context->ignore_fcs |= MLX4_IGNORE_FCS_MASK;
	else
		context->ignore_fcs &= ~MLX4_IGNORE_FCS_MASK;

	in_mod = MLX4_SET_PORT_GENERAL << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, 1, MLX4_CMD_SET_PORT,
		       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);

	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}
