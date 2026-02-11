intel_pch_thermal_probe(struct pci_dev *pdev,
				   const struct pci_device_id *id)
{
	struct pch_thermal_device *ptd;
	int err;
	int nr_trips;
	char *dev_name;

	ptd = devm_kzalloc(&pdev->dev, sizeof(*ptd), GFP_KERNEL);
	if (!ptd)
		return -ENOMEM;

	switch (pdev->device) {
	case PCH_THERMAL_DID_WPT:
		ptd->ops = &pch_dev_ops_wpt;
		dev_name = "pch_wildcat_point";
		break;
	default:
		dev_err(&pdev->dev, "unknown pch thermal device\n");
		return -ENODEV;
	}

	pci_set_drvdata(pdev, ptd);
	ptd->pdev = pdev;

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "failed to enable pci device\n");
		return err;
	}

	err = pci_request_regions(pdev, driver_name);
	if (err) {
		dev_err(&pdev->dev, "failed to request pci region\n");
		goto error_disable;
	}

	ptd->hw_base = pci_ioremap_bar(pdev, 0);
	if (!ptd->hw_base) {
		err = -ENOMEM;
		dev_err(&pdev->dev, "failed to map mem base\n");
		goto error_release;
	}

	err = ptd->ops->hw_init(ptd, &nr_trips);
	if (err)
		goto error_cleanup;

	ptd->tzd = thermal_zone_device_register(dev_name, nr_trips, 0, ptd,
						&tzd_ops, NULL, 0, 0);
	if (IS_ERR(ptd->tzd)) {
		dev_err(&pdev->dev, "Failed to register thermal zone %s\n",
			dev_name);
		err = PTR_ERR(ptd->tzd);
		goto error_cleanup;
	}

	return 0;

error_cleanup:
	iounmap(ptd->hw_base);
error_release:
	pci_release_regions(pdev);
error_disable:
	pci_disable_device(pdev);
	dev_err(&pdev->dev, "pci device failed to probe\n");
	return err;
}
