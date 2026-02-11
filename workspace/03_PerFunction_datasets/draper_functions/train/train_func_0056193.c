mlx4_init_mr_table(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_mr_table *mr_table = &priv->mr_table;
	int err;


	if (mlx4_is_slave(dev))
		return 0;

	if (!is_power_of_2(dev->caps.num_mpts))
		return -EINVAL;

	err = mlx4_bitmap_init(&mr_table->mpt_bitmap, dev->caps.num_mpts,
			       ~0, dev->caps.reserved_mrws, 0);
	if (err)
		return err;

	err = mlx4_buddy_init(&mr_table->mtt_buddy,
			      ilog2((u32)dev->caps.num_mtts /
			      (1 << log_mtts_per_seg)));
	if (err)
		goto err_buddy;

	if (dev->caps.reserved_mtts) {
		priv->reserved_mtts =
			mlx4_alloc_mtt_range(dev,
					     fls(dev->caps.reserved_mtts - 1));
		if (priv->reserved_mtts < 0) {
			mlx4_warn(dev, "MTT table of order %u is too small\n",
				  mr_table->mtt_buddy.max_order);
			err = -ENOMEM;
			goto err_reserve_mtts;
		}
	}

	return 0;

err_reserve_mtts:
	mlx4_buddy_cleanup(&mr_table->mtt_buddy);

err_buddy:
	mlx4_bitmap_cleanup(&mr_table->mpt_bitmap);

	return err;
}
