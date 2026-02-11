ddb_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct ddb *dev;
	int stat = 0;
	int irq_flag = IRQF_SHARED;

	if (pci_enable_device(pdev) < 0)
		return -ENODEV;

	dev = vmalloc(sizeof(struct ddb));
	if (dev == NULL)
		return -ENOMEM;
	memset(dev, 0, sizeof(struct ddb));

	dev->pdev = pdev;
	pci_set_drvdata(pdev, dev);
	dev->info = (struct ddb_info *) id->driver_data;
	printk(KERN_INFO "DDBridge driver detected: %s\n", dev->info->name);

	dev->regs = ioremap(pci_resource_start(dev->pdev, 0),
			    pci_resource_len(dev->pdev, 0));
	if (!dev->regs) {
		stat = -ENOMEM;
		goto fail;
	}
	printk(KERN_INFO "HW %08x FW %08x\n", ddbreadl(0), ddbreadl(4));

#ifdef CONFIG_PCI_MSI
	if (pci_msi_enabled())
		stat = pci_enable_msi(dev->pdev);
	if (stat) {
		printk(KERN_INFO ": MSI not available.\n");
	} else {
		irq_flag = 0;
		dev->msi = 1;
	}
#endif
	stat = request_irq(dev->pdev->irq, irq_handler,
			   irq_flag, "DDBridge", (void *) dev);
	if (stat < 0)
		goto fail1;
	ddbwritel(0, DMA_BASE_WRITE);
	ddbwritel(0, DMA_BASE_READ);
	ddbwritel(0xffffffff, INTERRUPT_ACK);
	ddbwritel(0xfff0f, INTERRUPT_ENABLE);
	ddbwritel(0, MSI1_ENABLE);

	if (ddb_i2c_init(dev) < 0)
		goto fail1;
	ddb_ports_init(dev);
	if (ddb_buffers_alloc(dev) < 0) {
		printk(KERN_INFO ": Could not allocate buffer memory\n");
		goto fail2;
	}
	if (ddb_ports_attach(dev) < 0)
		goto fail3;
	ddb_device_create(dev);
	return 0;

fail3:
	ddb_ports_detach(dev);
	printk(KERN_ERR "fail3\n");
	ddb_ports_release(dev);
fail2:
	printk(KERN_ERR "fail2\n");
	ddb_buffers_free(dev);
fail1:
	printk(KERN_ERR "fail1\n");
	if (dev->msi)
		pci_disable_msi(dev->pdev);
	if (stat == 0)
		free_irq(dev->pdev->irq, dev);
fail:
	printk(KERN_ERR "fail\n");
	ddb_unmap(dev);
	pci_set_drvdata(pdev, NULL);
	pci_disable_device(pdev);
	return -1;
}
