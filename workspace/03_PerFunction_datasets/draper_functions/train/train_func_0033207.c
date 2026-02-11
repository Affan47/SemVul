mlx4_cleanup_eq_table(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int i;

	mlx4_MAP_EQ(dev, get_async_ev_mask(dev), 1,
		    priv->eq_table.eq[MLX4_EQ_ASYNC].eqn);

#ifdef CONFIG_RFS_ACCEL
	for (i = 1; i <= dev->caps.num_ports; i++) {
		if (mlx4_priv(dev)->port[i].rmap) {
			free_irq_cpu_rmap(mlx4_priv(dev)->port[i].rmap);
			mlx4_priv(dev)->port[i].rmap = NULL;
		}
	}
#endif
	mlx4_free_irqs(dev);

	for (i = 0; i < dev->caps.num_comp_vectors + 1; ++i)
		mlx4_free_eq(dev, &priv->eq_table.eq[i]);

	if (!mlx4_is_slave(dev))
		mlx4_unmap_clr_int(dev);

	mlx4_unmap_uar(dev);
	mlx4_bitmap_cleanup(&priv->eq_table.bitmap);

	kfree(priv->eq_table.uar_map);
}
