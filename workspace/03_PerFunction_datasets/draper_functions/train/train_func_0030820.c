mlx4_init_mcg_table(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int err;


	if (dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED)
		return 0;
	err = mlx4_bitmap_init(&priv->mcg_table.bitmap, dev->caps.num_amgms,
			       dev->caps.num_amgms - 1, 0, 0);
	if (err)
		return err;

	mutex_init(&priv->mcg_table.mutex);

	return 0;
}
