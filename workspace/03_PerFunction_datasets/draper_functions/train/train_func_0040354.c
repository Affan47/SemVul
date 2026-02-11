pcifront_xenbus_remove(struct xenbus_device *xdev)
{
	struct pcifront_device *pdev = dev_get_drvdata(&xdev->dev);
	if (pdev)
		free_pdev(pdev);

	return 0;
}
