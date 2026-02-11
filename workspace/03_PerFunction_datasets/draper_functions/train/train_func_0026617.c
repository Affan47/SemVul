st400_sense_handler( int fd, SANE_Byte *result, void *arg )
{

	SANE_Status status;

	fd = fd;
	arg = arg;

	switch( result[0] & 0x0f ) {
		case 0x0:
			status = SANE_STATUS_GOOD;
			break;
		case 0x1:
			DBG(DSENSE, "SCSI: sense RECOVERED_ERROR\n");
			status = SANE_STATUS_GOOD;
			break;
		case 0x2:
			DBG(DSENSE, "SCSI: sense NOT_READY\n");
			status = SANE_STATUS_DEVICE_BUSY;
			break;
		case 0x4:
			DBG(DSENSE, "SCSI: sense HARDWARE_ERROR\n");
			status = SANE_STATUS_IO_ERROR;
			break;
		case 0x5:
			DBG(DSENSE, "SCSI: sense ILLEGAL_REQUEST\n");
			status = SANE_STATUS_IO_ERROR;
			break;
		case 0x6:
			DBG(DSENSE, "SCSI: sense UNIT_ATTENTION\n");
			status = SANE_STATUS_DEVICE_BUSY;
			break;
		case 0xb:
			DBG(DSENSE, "SCSI: sense ABORTED_COMMAND\n");
			status = SANE_STATUS_CANCELLED;
			break;
		default:
			DBG(DSENSE, "SCSI: sense unknown (%d)\n", result[0] & 0x0f);
			status = SANE_STATUS_IO_ERROR;
			break;
	}
	return status;
}
