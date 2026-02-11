nfcwilink_remove(struct platform_device *pdev)
{
	struct nfcwilink *drv = dev_get_drvdata(&pdev->dev);
	struct nci_dev *ndev;

	if (!drv)
		return -EFAULT;

	ndev = drv->ndev;

	nci_unregister_device(ndev);
	nci_free_device(ndev);

	return 0;
}
