mlx4_alloc_mtt_range(struct mlx4_dev *dev, int order)
{
	u64 in_param = 0;
	u64 out_param;
	int err;

	if (mlx4_is_mfunc(dev)) {
		set_param_l(&in_param, order);
		err = mlx4_cmd_imm(dev, in_param, &out_param, RES_MTT,
						       RES_OP_RESERVE_AND_MAP,
						       MLX4_CMD_ALLOC_RES,
						       MLX4_CMD_TIME_CLASS_A,
						       MLX4_CMD_WRAPPED);
		if (err)
			return -1;
		return get_param_l(&out_param);
	}
	return __mlx4_alloc_mtt_range(dev, order);
}
