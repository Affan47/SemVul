ipc_plat_probe(struct platform_device *pdev)
{
	struct resource *res;
	int ret;

	ipcdev.dev = &pdev->dev;
	ipcdev.irq_mode = IPC_TRIGGER_MODE_IRQ;
	init_completion(&ipcdev.cmd_complete);

	ipcdev.irq = platform_get_irq(pdev, 0);
	if (ipcdev.irq < 0) {
		dev_err(&pdev->dev, "Failed to get irq\n");
		return -EINVAL;
	}

	ret = ipc_plat_get_res(pdev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request resource\n");
		return ret;
	}

	ret = ipc_create_pmc_devices();
	if (ret) {
		dev_err(&pdev->dev, "Failed to create pmc devices\n");
		goto err_device;
	}

	if (request_irq(ipcdev.irq, ioc, 0, "intel_pmc_ipc", &ipcdev)) {
		dev_err(&pdev->dev, "Failed to request irq\n");
		ret = -EBUSY;
		goto err_irq;
	}

	ret = sysfs_create_group(&pdev->dev.kobj, &intel_ipc_group);
	if (ret) {
		dev_err(&pdev->dev, "Failed to create sysfs group %d\n",
			ret);
		goto err_sys;
	}

	return 0;
err_sys:
	free_irq(ipcdev.irq, &ipcdev);
err_irq:
	platform_device_unregister(ipcdev.tco_dev);
	platform_device_unregister(ipcdev.punit_dev);
	platform_device_unregister(ipcdev.telemetry_dev);
err_device:
	iounmap(ipcdev.ipc_base);
	res = platform_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_IPC_INDEX);
	if (res)
		release_mem_region(res->start, PLAT_RESOURCE_IPC_SIZE);
	return ret;
}
