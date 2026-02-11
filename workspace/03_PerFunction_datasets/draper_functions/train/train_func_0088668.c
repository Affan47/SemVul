smi_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct smi_dev *dev;
	int ret = -ENOMEM;

	if (pci_enable_device(pdev) < 0)
		return -ENODEV;

	dev = kzalloc(sizeof(struct smi_dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto err_pci_disable_device;
	}

	dev->pci_dev = pdev;
	pci_set_drvdata(pdev, dev);
	dev->info = (struct smi_cfg_info *) id->driver_data;
	dev_info(&dev->pci_dev->dev,
		"card detected: %s\n", dev->info->name);

	dev->nr = dev->info->type;
	dev->lmmio = ioremap(pci_resource_start(dev->pci_dev, 0),
			    pci_resource_len(dev->pci_dev, 0));
	if (!dev->lmmio) {
		ret = -ENOMEM;
		goto err_kfree;
	}


	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret < 0)
		goto err_pci_iounmap;

	pci_set_master(pdev);

	ret = smi_hw_init(dev);
	if (ret < 0)
		goto err_pci_iounmap;

	ret = smi_i2c_init(dev);
	if (ret < 0)
		goto err_pci_iounmap;

	if (dev->info->ts_0) {
		ret = smi_port_attach(dev, &dev->ts_port[0], 0);
		if (ret < 0)
			goto err_del_i2c_adaptor;
	}

	if (dev->info->ts_1) {
		ret = smi_port_attach(dev, &dev->ts_port[1], 1);
		if (ret < 0)
			goto err_del_port0_attach;
	}

	ret = smi_ir_init(dev);
	if (ret < 0)
		goto err_del_port1_attach;

#ifdef CONFIG_PCI_MSI
	if (pci_msi_enabled())
		ret = pci_enable_msi(dev->pci_dev);
	if (ret)
		dev_info(&dev->pci_dev->dev, "MSI not available.\n");
#endif

	ret = request_irq(dev->pci_dev->irq, smi_irq_handler,
			   IRQF_SHARED, "SMI_PCIE", dev);
	if (ret < 0)
		goto err_del_ir;

	smi_ir_start(&dev->ir);
	return 0;

err_del_ir:
	smi_ir_exit(dev);
err_del_port1_attach:
	if (dev->info->ts_1)
		smi_port_detach(&dev->ts_port[1]);
err_del_port0_attach:
	if (dev->info->ts_0)
		smi_port_detach(&dev->ts_port[0]);
err_del_i2c_adaptor:
	smi_i2c_exit(dev);
err_pci_iounmap:
	iounmap(dev->lmmio);
err_kfree:
	pci_set_drvdata(pdev, NULL);
	kfree(dev);
err_pci_disable_device:
	pci_disable_device(pdev);
	return ret;
}
