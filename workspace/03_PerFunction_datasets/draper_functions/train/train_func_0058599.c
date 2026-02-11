mlx4_cleanup_cq_table(struct mlx4_dev *dev)
{
	if (mlx4_is_slave(dev))
		return;

	mlx4_bitmap_cleanup(&mlx4_priv(dev)->cq_table.bitmap);
}
