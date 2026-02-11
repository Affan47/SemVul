sil_sata_reset_poll(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	void __iomem *sata_status_addr
		= (void __iomem *)hwif->sata_scr[SATA_STATUS_OFFSET];

	if (sata_status_addr) {

		u32 sata_stat = readl(sata_status_addr);

		if ((sata_stat & 0x03) != 0x03) {
			printk(KERN_WARNING "%s: reset phy dead, status=0x%08x\n",
					    hwif->name, sata_stat);
			return -ENXIO;
		}
	}

	return 0;
}
