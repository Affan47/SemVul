whci_add_cap(struct whci_card *card, int n)
{
	struct umc_dev *umc;
	u64 capdata;
	int bar, err;

	umc = umc_device_create(&card->pci->dev, n);
	if (umc == NULL)
		return -ENOMEM;

	capdata = le_readq(card->uwbbase + UWBCAPDATA(n));

	bar = UWBCAPDATA_TO_BAR(capdata) << 1;

	capdata = whci_capdata_quirks(card, capdata);


	umc->version         = UWBCAPDATA_TO_VERSION(capdata);
	umc->cap_id          = n == 0 ? 0 : UWBCAPDATA_TO_CAP_ID(capdata);
	umc->bar	     = bar;
	umc->resource.start  = pci_resource_start(card->pci, bar)
		+ UWBCAPDATA_TO_OFFSET(capdata);
	umc->resource.end    = umc->resource.start
		+ (n == 0 ? 0x20 : UWBCAPDATA_TO_SIZE(capdata)) - 1;
	umc->resource.name   = dev_name(&umc->dev);
	umc->resource.flags  = card->pci->resource[bar].flags;
	umc->resource.parent = &card->pci->resource[bar];
	umc->irq             = card->pci->irq;

	err = umc_device_register(umc);
	if (err < 0)
		goto error;
	card->devs[n] = umc;
	return 0;

error:
	kfree(umc);
	return err;
}
