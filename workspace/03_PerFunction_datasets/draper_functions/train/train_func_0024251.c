ssb_hcd_probe(struct ssb_device *dev,
				   const struct ssb_device_id *id)
{
	int err, tmp;
	int start, len;
	u16 chipid_top;
	u16 coreid = dev->id.coreid;
	struct ssb_hcd_device *usb_dev;


	chipid_top = (dev->bus->chip_id & 0xFF00);
	if (chipid_top != 0x4700 && chipid_top != 0x5300)
		return -ENODEV;


	if (dma_set_mask_and_coherent(dev->dma_dev, DMA_BIT_MASK(32)))
		return -EOPNOTSUPP;

	usb_dev = devm_kzalloc(dev->dev, sizeof(struct ssb_hcd_device),
			       GFP_KERNEL);
	if (!usb_dev)
		return -ENOMEM;


	usb_dev->enable_flags = ssb_hcd_init_chip(dev);

	tmp = ssb_read32(dev, SSB_ADMATCH0);

	start = ssb_admatch_base(tmp);
	len = (coreid == SSB_DEV_USB20_HOST) ? 0x800 : ssb_admatch_size(tmp);
	usb_dev->ohci_dev = ssb_hcd_create_pdev(dev, true, start, len);
	if (IS_ERR(usb_dev->ohci_dev))
		return PTR_ERR(usb_dev->ohci_dev);

	if (coreid == SSB_DEV_USB20_HOST) {
		start = ssb_admatch_base(tmp) + 0x800;
		usb_dev->ehci_dev = ssb_hcd_create_pdev(dev, false, start, len);
		if (IS_ERR(usb_dev->ehci_dev)) {
			err = PTR_ERR(usb_dev->ehci_dev);
			goto err_unregister_ohci_dev;
		}
	}

	ssb_set_drvdata(dev, usb_dev);
	return 0;

err_unregister_ohci_dev:
	platform_device_unregister(usb_dev->ohci_dev);
	return err;
}
