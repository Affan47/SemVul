idetape_media_access_finished(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	idetape_tape_t *tape = drive->driver_data;
	struct ide_atapi_pc *pc = drive->pc;
	u8 stat;

	stat = hwif->tp_ops->read_status(hwif);

	if (stat & ATA_DSC) {
		if (stat & ATA_ERR) {

			if (pc->c[0] != TEST_UNIT_READY)
				printk(KERN_ERR "ide-tape: %s: I/O error, ",
						tape->name);

			ide_retry_pc(drive);
			return ide_stopped;
		}
		pc->error = 0;
	} else {
		pc->error = IDE_DRV_ERROR_GENERAL;
		drive->failed_pc = NULL;
	}
	drive->pc_callback(drive, 0);
	return ide_stopped;
}
