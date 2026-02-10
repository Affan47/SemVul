cs5535_mfd_probe(struct pci_dev *pdev,
		const struct pci_device_id *id)
{
	int err, i;

	err = pci_enable_device(pdev);
	if (err)
		return err;


	for (i = 0; i < ARRAY_SIZE(cs5535_mfd_cells); i++) {
		int bar = cs5535_mfd_cells[i].id;
		struct resource *r = &cs5535_mfd_resources[bar];

		r->flags = IORESOURCE_IO;
		r->start = pci_resource_start(pdev, bar);
		r->end = pci_resource_end(pdev, bar);


		cs5535_mfd_cells[i].id = 0;
	}

	err = mfd_add_devices(&pdev->dev, -1, cs5535_mfd_cells,
			      ARRAY_SIZE(cs5535_mfd_cells), NULL, 0, NULL);
	if (err) {
		dev_err(&pdev->dev, "MFD add devices failed: %d\n", err);
		goto err_disable;
	}
	cs5535_clone_olpc_cells();

	dev_info(&pdev->dev, "%zu devices registered.\n",
			ARRAY_SIZE(cs5535_mfd_cells));

	return 0;

err_disable:
	pci_disable_device(pdev);
	return err;
}
