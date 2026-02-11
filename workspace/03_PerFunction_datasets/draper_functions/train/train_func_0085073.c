ipr_store_diagnostics(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *)shost->hostdata;
	unsigned long lock_flags = 0;
	int rc = count;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	while (ioa_cfg->in_reset_reload) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		wait_event(ioa_cfg->reset_wait_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	}

	ioa_cfg->errors_logged = 0;
	ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NORMAL);

	if (ioa_cfg->in_reset_reload) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		wait_event(ioa_cfg->reset_wait_q, !ioa_cfg->in_reset_reload);


		msleep(1000);
	} else {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		return -EIO;
	}

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	if (ioa_cfg->in_reset_reload || ioa_cfg->errors_logged)
		rc = -EIO;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	return rc;
}
