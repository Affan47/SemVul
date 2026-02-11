mlx4_unload_one(struct pci_dev *pdev)
{
	struct mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	struct mlx4_dev  *dev  = persist->dev;
	struct mlx4_priv *priv = mlx4_priv(dev);
	int               pci_dev_data;
	int p, i;

	if (priv->removed)
		return;


	for (i = 0; i < dev->caps.num_ports; i++) {
		dev->persist->curr_port_type[i] = dev->caps.port_type[i + 1];
		dev->persist->curr_port_poss_type[i] = dev->caps.
						       possible_type[i + 1];
	}

	pci_dev_data = priv->pci_dev_data;

	mlx4_stop_sense(dev);
	mlx4_unregister_device(dev);

	for (p = 1; p <= dev->caps.num_ports; p++) {
		mlx4_cleanup_port_info(&priv->port[p]);
		mlx4_CLOSE_PORT(dev, p);
	}

	if (mlx4_is_master(dev))
		mlx4_free_resource_tracker(dev,
					   RES_TR_FREE_SLAVES_ONLY);

	mlx4_cleanup_default_counters(dev);
	if (!mlx4_is_slave(dev))
		mlx4_cleanup_counters_table(dev);
	mlx4_cleanup_qp_table(dev);
	mlx4_cleanup_srq_table(dev);
	mlx4_cleanup_cq_table(dev);
	mlx4_cmd_use_polling(dev);
	mlx4_cleanup_eq_table(dev);
	mlx4_cleanup_mcg_table(dev);
	mlx4_cleanup_mr_table(dev);
	mlx4_cleanup_xrcd_table(dev);
	mlx4_cleanup_pd_table(dev);

	if (mlx4_is_master(dev))
		mlx4_free_resource_tracker(dev,
					   RES_TR_FREE_STRUCTS_ONLY);

	iounmap(priv->kar);
	mlx4_uar_free(dev, &priv->driver_uar);
	mlx4_cleanup_uar_table(dev);
	if (!mlx4_is_slave(dev))
		mlx4_clear_steering(dev);
	mlx4_free_eq_table(dev);
	if (mlx4_is_master(dev))
		mlx4_multi_func_cleanup(dev);
	mlx4_close_hca(dev);
	mlx4_close_fw(dev);
	if (mlx4_is_slave(dev))
		mlx4_multi_func_cleanup(dev);
	mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_ALL);

	if (dev->flags & MLX4_FLAG_MSI_X)
		pci_disable_msix(pdev);

	if (!mlx4_is_slave(dev))
		mlx4_free_ownership(dev);

	kfree(dev->caps.qp0_qkey);
	kfree(dev->caps.qp0_tunnel);
	kfree(dev->caps.qp0_proxy);
	kfree(dev->caps.qp1_tunnel);
	kfree(dev->caps.qp1_proxy);
	kfree(dev->dev_vfs);

	mlx4_clean_dev(dev);
	priv->pci_dev_data = pci_dev_data;
	priv->removed = 1;
}
