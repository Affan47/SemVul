free_pdev(struct xen_pcibk_device *pdev)
{
	if (pdev->be_watching) {
		unregister_xenbus_watch(&pdev->be_watch);
		pdev->be_watching = 0;
	}

	xen_pcibk_disconnect(pdev);


	xen_pcibk_release_devices(pdev);

	dev_set_drvdata(&pdev->xdev->dev, NULL);
	pdev->xdev = NULL;

	kfree(pdev);
}
