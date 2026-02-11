mlx4_cleanup_counters_table(struct mlx4_dev *dev)
{
	if (!(dev->caps.flags & MLX4_DEV_CAP_FLAG_COUNTERS))
		return;

	if (!dev->caps.max_counters)
		return;

	mlx4_bitmap_cleanup(&mlx4_priv(dev)->counters_bitmap);
}
