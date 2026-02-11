twl_sysfs_compat_info(struct file *filp, struct kobject *kobj,
				     struct bin_attribute *bin_attr,
				     char *outbuf, loff_t offset, size_t count)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct Scsi_Host *shost = class_to_shost(dev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)shost->hostdata;
	unsigned long flags = 0;
	ssize_t ret;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	spin_lock_irqsave(tw_dev->host->host_lock, flags);
	ret = memory_read_from_buffer(outbuf, count, &offset, &tw_dev->tw_compat_info, sizeof(TW_Compatibility_Info));
	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);

	return ret;
}
