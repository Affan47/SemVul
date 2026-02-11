ide_cd_breathe(ide_drive_t *drive, struct request *rq)
{

	struct cdrom_info *info = drive->driver_data;

	if (!rq->errors)
		info->write_timeout = jiffies +	ATAPI_WAIT_WRITE_BUSY;

	rq->errors = 1;

	if (time_after(jiffies, info->write_timeout))
		return 0;
	else {


		blk_delay_queue(drive->queue, 1);
		return 1;
	}
}
