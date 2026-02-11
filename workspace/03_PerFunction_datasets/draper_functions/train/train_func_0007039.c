mlx5_sriov_cleanup(struct mlx5_core_dev *dev)
{
	struct pci_dev *pdev = dev->pdev;
	int err;

	if (!mlx5_core_is_pf(dev))
		return 0;

	err = mlx5_core_sriov_configure(pdev, 0);
	if (err)
		return err;

	return 0;
}
