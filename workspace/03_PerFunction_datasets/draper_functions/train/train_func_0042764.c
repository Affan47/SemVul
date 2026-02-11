via_sd_probe(struct pci_dev *pcidev,
				    const struct pci_device_id *id)
{
	struct mmc_host *mmc;
	struct via_crdr_mmc_host *sdhost;
	u32 base, len;
	u8  gatt;
	int ret;

	pr_info(DRV_NAME
		": VIA SDMMC controller found at %s [%04x:%04x] (rev %x)\n",
		pci_name(pcidev), (int)pcidev->vendor, (int)pcidev->device,
		(int)pcidev->revision);

	ret = pci_enable_device(pcidev);
	if (ret)
		return ret;

	ret = pci_request_regions(pcidev, DRV_NAME);
	if (ret)
		goto disable;

	pci_write_config_byte(pcidev, VIA_CRDR_PCI_WORK_MODE, 0);
	pci_write_config_byte(pcidev, VIA_CRDR_PCI_DBG_MODE, 0);

	mmc = mmc_alloc_host(sizeof(struct via_crdr_mmc_host), &pcidev->dev);
	if (!mmc) {
		ret = -ENOMEM;
		goto release;
	}

	sdhost = mmc_priv(mmc);
	sdhost->mmc = mmc;
	dev_set_drvdata(&pcidev->dev, sdhost);

	len = pci_resource_len(pcidev, 0);
	base = pci_resource_start(pcidev, 0);
	sdhost->mmiobase = ioremap_nocache(base, len);
	if (!sdhost->mmiobase) {
		ret = -ENOMEM;
		goto free_mmc_host;
	}

	sdhost->sdhc_mmiobase =
		sdhost->mmiobase + VIA_CRDR_SDC_OFF;
	sdhost->ddma_mmiobase =
		sdhost->mmiobase + VIA_CRDR_DDMA_OFF;
	sdhost->pcictrl_mmiobase =
		sdhost->mmiobase + VIA_CRDR_PCICTRL_OFF;

	sdhost->power = MMC_VDD_165_195;

	gatt = VIA_CRDR_PCICLKGATT_3V3 | VIA_CRDR_PCICLKGATT_PAD_PWRON;
	writeb(gatt, sdhost->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	via_pwron_sleep(sdhost);
	gatt |= VIA_CRDR_PCICLKGATT_SFTRST;
	writeb(gatt, sdhost->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	msleep(3);

	via_init_mmc_host(sdhost);

	ret =
	    request_irq(pcidev->irq, via_sdc_isr, IRQF_SHARED, DRV_NAME,
			sdhost);
	if (ret)
		goto unmap;

	writeb(VIA_CRDR_PCIINTCTRL_SDCIRQEN,
	       sdhost->pcictrl_mmiobase + VIA_CRDR_PCIINTCTRL);
	writeb(VIA_CRDR_PCITMOCTRL_1024MS,
	       sdhost->pcictrl_mmiobase + VIA_CRDR_PCITMOCTRL);


	if (pcidev->subsystem_vendor == PCI_VENDOR_ID_LENOVO &&
	    pcidev->subsystem_device == 0x3891)
		sdhost->quirks = VIA_CRDR_QUIRK_300MS_PWRDELAY;

	mmc_add_host(mmc);

	return 0;

unmap:
	iounmap(sdhost->mmiobase);
free_mmc_host:
	dev_set_drvdata(&pcidev->dev, NULL);
	mmc_free_host(mmc);
release:
	pci_release_regions(pcidev);
disable:
	pci_disable_device(pcidev);

	return ret;
}
