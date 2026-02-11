__mlx4_ib_destroy_flow(struct mlx4_dev *dev, u64 reg_id)
{
	int err;
	err = mlx4_cmd(dev, reg_id, 0, 0,
		       MLX4_QP_FLOW_STEERING_DETACH, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_WRAPPED);
	if (err)
		pr_err("Fail to detach network rule. registration id = 0x%llx\n",
		       reg_id);
	return err;
}
