wdt_probe(struct pci_dev *pdev,
			       const struct pci_device_id *ent)
{
	unsigned char conf;
	int ret = -ENODEV;

	if (pci_enable_device(pdev)) {
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		return -ENODEV;
	}


	if (allocate_resource(&iomem_resource, &wdt_res, VIA_WDT_MMIO_LEN,
			      0xf0000000, 0xffffff00, 0xff, NULL, NULL)) {
		dev_err(&pdev->dev, "MMIO allocation failed\n");
		goto err_out_disable_device;
	}

	pci_write_config_dword(pdev, VIA_WDT_MMIO_BASE, wdt_res.start);
	pci_read_config_byte(pdev, VIA_WDT_CONF, &conf);
	conf |= VIA_WDT_CONF_ENABLE | VIA_WDT_CONF_MMIO;
	pci_write_config_byte(pdev, VIA_WDT_CONF, conf);

	pci_read_config_dword(pdev, VIA_WDT_MMIO_BASE, &mmio);
	if (mmio) {
		dev_info(&pdev->dev, "VIA Chipset watchdog MMIO: %x\n", mmio);
	} else {
		dev_err(&pdev->dev, "MMIO setting failed. Check BIOS.\n");
		goto err_out_resource;
	}

	if (!request_mem_region(mmio, VIA_WDT_MMIO_LEN, "via_wdt")) {
		dev_err(&pdev->dev, "MMIO region busy\n");
		goto err_out_resource;
	}

	wdt_mem = ioremap(mmio, VIA_WDT_MMIO_LEN);
	if (wdt_mem == NULL) {
		dev_err(&pdev->dev, "cannot remap VIA wdt MMIO registers\n");
		goto err_out_release;
	}

	if (timeout < 1 || timeout > WDT_TIMEOUT_MAX)
		timeout = WDT_TIMEOUT;

	wdt_dev.timeout = timeout;
	wdt_dev.parent = &pdev->dev;
	watchdog_set_nowayout(&wdt_dev, nowayout);
	if (readl(wdt_mem) & VIA_WDT_FIRED)
		wdt_dev.bootstatus |= WDIOF_CARDRESET;

	ret = watchdog_register_device(&wdt_dev);
	if (ret)
		goto err_out_iounmap;


	mod_timer(&timer, jiffies + WDT_HEARTBEAT);
	return 0;

err_out_iounmap:
	iounmap(wdt_mem);
err_out_release:
	release_mem_region(mmio, VIA_WDT_MMIO_LEN);
err_out_resource:
	release_resource(&wdt_res);
err_out_disable_device:
	pci_disable_device(pdev);
	return ret;
}
