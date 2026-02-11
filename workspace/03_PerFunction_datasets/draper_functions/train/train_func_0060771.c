sercos3_pci_probe(struct pci_dev *dev,
				       const struct pci_device_id *id)
{
	struct uio_info *info;
	struct sercos3_priv *priv;
	int i;

	info = kzalloc(sizeof(struct uio_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	priv = kzalloc(sizeof(struct sercos3_priv), GFP_KERNEL);
	if (!priv)
		goto out_free;

	if (pci_enable_device(dev))
		goto out_free_priv;

	if (pci_request_regions(dev, "sercos3"))
		goto out_disable;


	if (sercos3_setup_iomem(dev, info, 0, 0))
		goto out_unmap;
	if (sercos3_setup_iomem(dev, info, 1, 2))
		goto out_unmap;
	if (sercos3_setup_iomem(dev, info, 2, 3))
		goto out_unmap;
	if (sercos3_setup_iomem(dev, info, 3, 4))
		goto out_unmap;
	if (sercos3_setup_iomem(dev, info, 4, 5))
		goto out_unmap;

	spin_lock_init(&priv->ier0_cache_lock);
	info->priv = priv;
	info->name = "Sercos_III_PCI";
	info->version = "0.0.1";
	info->irq = dev->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = sercos3_handler;
	info->irqcontrol = sercos3_irqcontrol;

	pci_set_drvdata(dev, info);

	if (uio_register_device(&dev->dev, info))
		goto out_unmap;

	return 0;

out_unmap:
	for (i = 0; i < 5; i++) {
		if (info->mem[i].internal_addr)
			iounmap(info->mem[i].internal_addr);
	}
	pci_release_regions(dev);
out_disable:
	pci_disable_device(dev);
out_free_priv:
	kfree(priv);
out_free:
	kfree(info);
	return -ENODEV;
}
