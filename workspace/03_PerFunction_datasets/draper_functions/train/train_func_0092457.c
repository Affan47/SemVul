mlx4_HW2SW_CQ(struct mlx4_dev *dev, struct mlx4_cmd_mailbox *mailbox,
			 int cq_num)
{
	return mlx4_cmd_box(dev, 0, mailbox ? mailbox->dma : 0,
			    cq_num, mailbox ? 0 : 1, MLX4_CMD_HW2SW_CQ,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
}
