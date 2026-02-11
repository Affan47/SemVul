ata_get_xlat_func(struct ata_device *dev, u8 cmd)
{
	switch (cmd) {
	case READ_6:
	case READ_10:
	case READ_16:

	case WRITE_6:
	case WRITE_10:
	case WRITE_16:
		return ata_scsi_rw_xlat;

	case WRITE_SAME_16:
		return ata_scsi_write_same_xlat;

	case SYNCHRONIZE_CACHE:
		if (ata_try_flush_cache(dev))
			return ata_scsi_flush_xlat;
		break;

	case VERIFY:
	case VERIFY_16:
		return ata_scsi_verify_xlat;

	case ATA_12:
	case ATA_16:
		return ata_scsi_pass_thru;

	case MODE_SELECT:
	case MODE_SELECT_10:
		return ata_scsi_mode_select_xlat;
		break;

	case START_STOP:
		return ata_scsi_start_stop_xlat;
	}

	return NULL;
}
