hpt366_set_mode(struct ata_port *ap, struct ata_device *adev,
			    u8 mode)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 addr = 0x40 + 4 * adev->devno;
	u32 mask, reg, t;


	if (mode < XFER_MW_DMA_0)
		mask = 0xc1f8ffff;
	else if (mode < XFER_UDMA_0)
		mask = 0x303800ff;
	else
		mask = 0x30070000;

	t = hpt36x_find_mode(ap, mode);


	pci_read_config_dword(pdev, addr, &reg);
	reg = ((reg & ~mask) | (t & mask)) & ~0xc0000000;
	pci_write_config_dword(pdev, addr, reg);
}
