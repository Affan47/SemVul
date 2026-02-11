tc86c001_timer_expiry(ide_drive_t *drive)
{
	ide_hwif_t *hwif	= drive->hwif;
	ide_expiry_t *expiry	= ide_get_hwifdata(hwif);
	u8 dma_stat		= inb(hwif->dma_base + ATA_DMA_STATUS);


	hwif->expiry = expiry;

	if ((dma_stat & 5) == 1) {
		unsigned long sc_base	= hwif->config_data;
		unsigned long twcr_port	= sc_base + (drive->dn ? 0x06 : 0x04);
		u8 dma_cmd		= inb(hwif->dma_base + ATA_DMA_CMD);

		printk(KERN_WARNING "%s: DMA interrupt possibly stuck, "
		       "attempting recovery...\n", drive->name);


		outb(dma_cmd & ~0x01, hwif->dma_base + ATA_DMA_CMD);


		outw(0, sc_base + 0x0a);
		outw(0, twcr_port);


		outb(0x00, hwif->dma_base + ATA_DMA_CMD);

		outb(0x01, hwif->dma_base + ATA_DMA_CMD);


		return WAIT_MIN_SLEEP;
	}


	if (likely(expiry != NULL))
		return expiry(drive);


	return -1;
}
