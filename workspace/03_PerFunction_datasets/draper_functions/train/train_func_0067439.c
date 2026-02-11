__scsi_add_device(struct Scsi_Host *shost, uint channel,
				      uint id, u64 lun, void *hostdata)
{
	struct scsi_device *sdev = ERR_PTR(-ENODEV);
	struct device *parent = &shost->shost_gendev;
	struct scsi_target *starget;

	if (strncmp(scsi_scan_type, "none", 4) == 0)
		return ERR_PTR(-ENODEV);

	starget = scsi_alloc_target(parent, channel, id);
	if (!starget)
		return ERR_PTR(-ENOMEM);
	scsi_autopm_get_target(starget);

	mutex_lock(&shost->scan_mutex);
	if (!shost->async_scan)
		scsi_complete_async_scans();

	if (scsi_host_scan_allowed(shost) && scsi_autopm_get_host(shost) == 0) {
		scsi_probe_and_add_lun(starget, lun, NULL, &sdev, 1, hostdata);
		scsi_autopm_put_host(shost);
	}
	mutex_unlock(&shost->scan_mutex);
	scsi_autopm_put_target(starget);


	scsi_target_reap(starget);
	put_device(&starget->dev);

	return sdev;
}
