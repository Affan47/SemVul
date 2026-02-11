mlx4_get_internal_clock_params(struct mlx4_dev *dev,
				   struct mlx4_clock_params *params)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	if (mlx4_is_slave(dev))
		return -ENOTSUPP;

	if (!params)
		return -EINVAL;

	params->bar = priv->fw.clock_bar;
	params->offset = priv->fw.clock_offset;
	params->size = MLX4_CLOCK_SIZE;

	return 0;
}
