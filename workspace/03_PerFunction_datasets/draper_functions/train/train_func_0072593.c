qp_detach(struct mlx4_dev *dev, struct mlx4_qp *qp,
		     u8 gid[16], enum mlx4_protocol prot,
		     enum mlx4_steer_type type, u64 reg_id)
{
	switch (dev->caps.steering_mode) {
	case MLX4_STEERING_MODE_DEVICE_MANAGED:
		return mlx4_flow_detach(dev, reg_id);
	case MLX4_STEERING_MODE_B0:
		return mlx4_qp_detach_common(dev, qp, gid, prot, type);
	default:
		return -EINVAL;
	}
}
