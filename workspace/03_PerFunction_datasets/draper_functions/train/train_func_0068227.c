ide_pio_cycle_time(ide_drive_t *drive, u8 pio)
{
	u16 *id = drive->id;
	struct ide_timing *t = ide_timing_find_mode(XFER_PIO_0 + pio);
	u16 cycle = 0;

	if (id[ATA_ID_FIELD_VALID] & 2) {
		if (ata_id_has_iordy(drive->id))
			cycle = id[ATA_ID_EIDE_PIO_IORDY];
		else
			cycle = id[ATA_ID_EIDE_PIO];


		if (pio < 3 && cycle < t->cycle)
			cycle = 0;


		if (pio > 4 && ata_id_is_cfa(id))
			cycle = 0;
	}

	return cycle ? cycle : t->cycle;
}
