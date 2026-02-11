serverworks_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	static const u8 pio_mode[] = { 0x5d, 0x47, 0x34, 0x22, 0x20 };
	int offset = 1 + 2 * ap->port_no - adev->devno;
	int devbits = (2 * ap->port_no + adev->devno) * 4;
	u16 csb5_pio;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int pio = adev->pio_mode - XFER_PIO_0;

	pci_write_config_byte(pdev, 0x40 + offset, pio_mode[pio]);


	if (serverworks_is_csb(pdev)) {
		pci_read_config_word(pdev, 0x4A, &csb5_pio);
		csb5_pio &= ~(0x0F << devbits);
		pci_write_config_word(pdev, 0x4A, csb5_pio | (pio << devbits));
	}
}
