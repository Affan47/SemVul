bgx_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int err;
	struct device *dev = &pdev->dev;
	struct bgx *bgx = NULL;
	u8 lmac;

	bgx = devm_kzalloc(dev, sizeof(*bgx), GFP_KERNEL);
	if (!bgx)
		return -ENOMEM;
	bgx->pdev = pdev;

	pci_set_drvdata(pdev, bgx);

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(dev, "Failed to enable PCI device\n");
		pci_set_drvdata(pdev, NULL);
		return err;
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		goto err_disable_device;
	}


	bgx->reg_base = pcim_iomap(pdev, PCI_CFG_REG_BAR_NUM, 0);
	if (!bgx->reg_base) {
		dev_err(dev, "BGX: Cannot map CSR memory space, aborting\n");
		err = -ENOMEM;
		goto err_release_regions;
	}
	bgx->bgx_id = (pci_resource_start(pdev, PCI_CFG_REG_BAR_NUM) >> 24) & 1;
	bgx->bgx_id += nic_get_node_id(pdev) * MAX_BGX_PER_CN88XX;

	bgx_vnic[bgx->bgx_id] = bgx;
	bgx_get_qlm_mode(bgx);

	err = bgx_init_phy(bgx);
	if (err)
		goto err_enable;

	bgx_init_hw(bgx);


	for (lmac = 0; lmac < bgx->lmac_count; lmac++) {
		err = bgx_lmac_enable(bgx, lmac);
		if (err) {
			dev_err(dev, "BGX%d failed to enable lmac%d\n",
				bgx->bgx_id, lmac);
			goto err_enable;
		}
	}

	return 0;

err_enable:
	bgx_vnic[bgx->bgx_id] = NULL;
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
	return err;
}
