mlx4_SET_PORT_PRIO2TC(struct mlx4_dev *dev, u8 port, u8 *prio2tc)
{
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_set_port_prio2tc_context *context;
	int err;
	u32 in_mod;
	int i;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	context = mailbox->buf;

	for (i = 0; i < MLX4_NUM_UP; i += 2)
		context->prio2tc[i >> 1] = prio2tc[i] << 4 | prio2tc[i + 1];

	in_mod = MLX4_SET_PORT_PRIO2TC << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, 1, MLX4_CMD_SET_PORT,
		       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);

	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}
