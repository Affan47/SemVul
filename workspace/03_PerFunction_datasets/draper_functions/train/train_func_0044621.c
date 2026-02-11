ipr_show_adapter_handle(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *)sdev->host->hostdata;
	struct ipr_resource_entry *res;
	unsigned long lock_flags = 0;
	ssize_t len = -ENXIO;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (struct ipr_resource_entry *)sdev->hostdata;
	if (res)
		len = snprintf(buf, PAGE_SIZE, "%08X\n", res->res_handle);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	return len;
}
