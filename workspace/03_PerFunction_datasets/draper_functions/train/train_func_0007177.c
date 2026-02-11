zatm_init_one(struct pci_dev *pci_dev,
			 const struct pci_device_id *ent)
{
	struct atm_dev *dev;
	struct zatm_dev *zatm_dev;
	int ret = -ENOMEM;

	zatm_dev = kmalloc(sizeof(*zatm_dev), GFP_KERNEL);
	if (!zatm_dev) {
		printk(KERN_EMERG "%s: memory shortage\n", DEV_LABEL);
		goto out;
	}

	dev = atm_dev_register(DEV_LABEL, &pci_dev->dev, &ops, -1, NULL);
	if (!dev)
		goto out_free;

	ret = pci_enable_device(pci_dev);
	if (ret < 0)
		goto out_deregister;

	ret = pci_request_regions(pci_dev, DEV_LABEL);
	if (ret < 0)
		goto out_disable;

	ret = dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(32));
	if (ret < 0)
		goto out_disable;

	zatm_dev->pci_dev = pci_dev;
	dev->dev_data = zatm_dev;
	zatm_dev->copper = (int)ent->driver_data;
	if ((ret = zatm_init(dev)) || (ret = zatm_start(dev)))
		goto out_release;

	pci_set_drvdata(pci_dev, dev);
	zatm_dev->more = zatm_boards;
	zatm_boards = dev;
	ret = 0;
out:
	return ret;

out_release:
	pci_release_regions(pci_dev);
out_disable:
	pci_disable_device(pci_dev);
out_deregister:
	atm_dev_deregister(dev);
out_free:
	kfree(zatm_dev);
	goto out;
}
