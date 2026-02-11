mlx4_SET_PORT_BEACON(struct mlx4_dev *dev, u8 port, u16 time)
{
	int err;
	struct mlx4_cmd_mailbox *mailbox;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	*((__be32 *)mailbox->buf) = cpu_to_be32(time);

	err = mlx4_cmd(dev, mailbox->dma, port, MLX4_SET_PORT_BEACON_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_NATIVE);

	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}
