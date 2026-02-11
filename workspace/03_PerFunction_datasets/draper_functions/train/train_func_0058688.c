mlx4_cleanup_mr_table(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_mr_table *mr_table = &priv->mr_table;

	if (mlx4_is_slave(dev))
		return;
	if (priv->reserved_mtts >= 0)
		mlx4_free_mtt_range(dev, priv->reserved_mtts,
				    fls(dev->caps.reserved_mtts - 1));
	mlx4_buddy_cleanup(&mr_table->mtt_buddy);
	mlx4_bitmap_cleanup(&mr_table->mpt_bitmap);
}
