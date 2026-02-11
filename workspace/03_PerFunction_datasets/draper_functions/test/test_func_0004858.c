esas2r_add_device(struct esas2r_adapter *a, u16 target_id)
{
	int ret;
	struct scsi_device *scsi_dev;

	scsi_dev = scsi_device_lookup(a->host, 0, target_id, 0);

	if (scsi_dev) {
		esas2r_log_dev(
			ESAS2R_LOG_WARN,
			&(scsi_dev->
			  sdev_gendev),
			"scsi device already exists at id %d", target_id);

		scsi_device_put(scsi_dev);
	} else {
		esas2r_log_dev(
			ESAS2R_LOG_INFO,
			&(a->host->
			  shost_gendev),
			"scsi_add_device() called for 0:%d:0",
			target_id);

		ret = scsi_add_device(a->host, 0, target_id, 0);
		if (ret) {
			esas2r_log_dev(
				ESAS2R_LOG_CRIT,
				&(a->host->
				  shost_gendev),
				"scsi_add_device failed with %d for id %d",
				ret, target_id);
		}
	}
}
