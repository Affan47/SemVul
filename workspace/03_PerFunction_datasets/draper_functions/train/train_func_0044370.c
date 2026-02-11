hpt36x_init_one(struct pci_dev *dev, const struct pci_device_id *id)
{
	static const struct ata_port_info info_hpt366 = {
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.port_ops = &hpt366_port_ops
	};
	const struct ata_port_info *ppi[] = { &info_hpt366, NULL };

	const void *hpriv = NULL;
	u32 reg1;
	int rc;

	rc = pcim_enable_device(dev);
	if (rc)
		return rc;


	if (dev->revision > 2)
		return -ENODEV;

	hpt36x_init_chipset(dev);

	pci_read_config_dword(dev, 0x40,  &reg1);


	switch ((reg1 & 0x700) >> 8) {
	case 9:
		hpriv = &hpt366_40;
		break;
	case 5:
		hpriv = &hpt366_25;
		break;
	default:
		hpriv = &hpt366_33;
		break;
	}

	return ata_pci_bmdma_init_one(dev, ppi, &hpt36x_sht, (void *)hpriv, 0);
}
