ccp_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct ccp_device *ccp;
	struct ccp_pci *ccp_pci;
	struct device *dev = &pdev->dev;
	unsigned int bar;
	int ret;

	ret = -ENOMEM;
	ccp = ccp_alloc_struct(dev);
	if (!ccp)
		goto e_err;

	ccp_pci = devm_kzalloc(dev, sizeof(*ccp_pci), GFP_KERNEL);
	if (!ccp_pci)
		goto e_err;

	ccp->dev_specific = ccp_pci;
	ccp->get_irq = ccp_get_irqs;
	ccp->free_irq = ccp_free_irqs;

	ret = pci_request_regions(pdev, "ccp");
	if (ret) {
		dev_err(dev, "pci_request_regions failed (%d)\n", ret);
		goto e_err;
	}

	ret = pci_enable_device(pdev);
	if (ret) {
		dev_err(dev, "pci_enable_device failed (%d)\n", ret);
		goto e_regions;
	}

	pci_set_master(pdev);

	ret = ccp_find_mmio_area(ccp);
	if (ret < 0)
		goto e_device;
	bar = ret;

	ret = -EIO;
	ccp->io_map = pci_iomap(pdev, bar, 0);
	if (!ccp->io_map) {
		dev_err(dev, "pci_iomap failed\n");
		goto e_device;
	}
	ccp->io_regs = ccp->io_map + IO_OFFSET;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(48));
	if (ret) {
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		if (ret) {
			dev_err(dev, "dma_set_mask_and_coherent failed (%d)\n",
				ret);
			goto e_iomap;
		}
	}

	dev_set_drvdata(dev, ccp);

	ret = ccp_init(ccp);
	if (ret)
		goto e_iomap;

	dev_notice(dev, "enabled\n");

	return 0;

e_iomap:
	pci_iounmap(pdev, ccp->io_map);

e_device:
	pci_disable_device(pdev);

e_regions:
	pci_release_regions(pdev);

e_err:
	dev_notice(dev, "initialization failed\n");
	return ret;
}
