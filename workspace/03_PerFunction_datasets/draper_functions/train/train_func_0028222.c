mlx5_irq_set_affinity_hints(struct mlx5_core_dev *mdev)
{
	int err;
	int i;

	for (i = 0; i < mdev->priv.eq_table.num_comp_vectors; i++) {
		err = mlx5_irq_set_affinity_hint(mdev, i);
		if (err)
			goto err_out;
	}

	return 0;

err_out:
	for (i--; i >= 0; i--)
		mlx5_irq_clear_affinity_hint(mdev, i);

	return err;
}
