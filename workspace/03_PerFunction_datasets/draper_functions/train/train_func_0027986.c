ide_input_data(ide_drive_t *drive, struct ide_cmd *cmd, void *buf,
		    unsigned int len)
{
	ide_hwif_t *hwif = drive->hwif;
	struct ide_io_ports *io_ports = &hwif->io_ports;
	unsigned long data_addr = io_ports->data_addr;
	unsigned int words = (len + 1) >> 1;
	u8 io_32bit = drive->io_32bit;
	u8 mmio = (hwif->host_flags & IDE_HFLAG_MMIO) ? 1 : 0;

	if (io_32bit) {
		unsigned long uninitialized_var(flags);

		if ((io_32bit & 2) && !mmio) {
			local_irq_save(flags);
			ata_vlb_sync(io_ports->nsect_addr);
		}

		words >>= 1;
		if (mmio)
			__ide_mm_insl((void __iomem *)data_addr, buf, words);
		else
			insl(data_addr, buf, words);

		if ((io_32bit & 2) && !mmio)
			local_irq_restore(flags);

		if (((len + 1) & 3) < 2)
			return;

		buf += len & ~3;
		words = 1;
	}

	if (mmio)
		__ide_mm_insw((void __iomem *)data_addr, buf, words);
	else
		insw(data_addr, buf, words);
}
