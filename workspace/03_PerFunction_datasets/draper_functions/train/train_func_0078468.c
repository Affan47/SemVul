sil680_cable_detect(struct ata_port *ap)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned long addr = sil680_selreg(ap, 0);
	u8 ata66;
	pci_read_config_byte(pdev, addr, &ata66);
	if (ata66 & 1)
		return ATA_CBL_PATA80;
	else
		return ATA_CBL_PATA40;
}
