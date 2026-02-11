ata_acpi_gtm_xfermask(struct ata_device *dev,
				    const struct ata_acpi_gtm *gtm)
{
	unsigned long xfer_mask = 0;
	unsigned int type;
	int unit;
	u8 mode;


	unit = dev->devno;
	if (!(gtm->flags & 0x10))
		unit = 0;


	mode = ata_timing_cycle2mode(ATA_SHIFT_PIO, gtm->drive[unit].pio);
	xfer_mask |= ata_xfer_mode2mask(mode);


	if (!(gtm->flags & (1 << (2 * unit))))
		type = ATA_SHIFT_MWDMA;
	else
		type = ATA_SHIFT_UDMA;

	mode = ata_timing_cycle2mode(type, gtm->drive[unit].dma);
	xfer_mask |= ata_xfer_mode2mask(mode);

	return xfer_mask;
}
