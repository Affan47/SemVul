mv_rw_multi_errata_sata24(struct ata_queued_cmd *qc)
{
	struct ata_taskfile *tf = &qc->tf;


	if ((tf->flags & ATA_TFLAG_WRITE) && is_multi_taskfile(tf)) {
		if (qc->dev->multi_count > 7) {
			switch (tf->command) {
			case ATA_CMD_WRITE_MULTI:
				tf->command = ATA_CMD_PIO_WRITE;
				break;
			case ATA_CMD_WRITE_MULTI_FUA_EXT:
				tf->flags &= ~ATA_TFLAG_FUA;

			case ATA_CMD_WRITE_MULTI_EXT:
				tf->command = ATA_CMD_PIO_WRITE_EXT;
				break;
			}
		}
	}
}
