mlx5_enable_msix(struct mlx5_core_dev *dev)
{
	struct mlx5_priv *priv = &dev->priv;
	struct mlx5_eq_table *table = &priv->eq_table;
	int num_eqs = 1 << MLX5_CAP_GEN(dev, log_max_eq);
	int nvec;
	int i;

	nvec = MLX5_CAP_GEN(dev, num_ports) * num_online_cpus() +
	       MLX5_EQ_VEC_COMP_BASE;
	nvec = min_t(int, nvec, num_eqs);
	if (nvec <= MLX5_EQ_VEC_COMP_BASE)
		return -ENOMEM;

	priv->msix_arr = kcalloc(nvec, sizeof(*priv->msix_arr), GFP_KERNEL);

	priv->irq_info = kcalloc(nvec, sizeof(*priv->irq_info), GFP_KERNEL);
	if (!priv->msix_arr || !priv->irq_info)
		goto err_free_msix;

	for (i = 0; i < nvec; i++)
		priv->msix_arr[i].entry = i;

	nvec = pci_enable_msix_range(dev->pdev, priv->msix_arr,
				     MLX5_EQ_VEC_COMP_BASE + 1, nvec);
	if (nvec < 0)
		return nvec;

	table->num_comp_vectors = nvec - MLX5_EQ_VEC_COMP_BASE;

	return 0;

err_free_msix:
	kfree(priv->irq_info);
	kfree(priv->msix_arr);
	return -ENOMEM;
}
