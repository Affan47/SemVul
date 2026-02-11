ata_scsi_park_show(struct device *device,
				  struct device_attribute *attr, char *buf)
{
	struct scsi_device *sdev = to_scsi_device(device);
	struct ata_port *ap;
	struct ata_link *link;
	struct ata_device *dev;
	unsigned long flags, now;
	unsigned int uninitialized_var(msecs);
	int rc = 0;

	ap = ata_shost_to_port(sdev->host);

	spin_lock_irqsave(ap->lock, flags);
	dev = ata_scsi_find_dev(ap, sdev);
	if (!dev) {
		rc = -ENODEV;
		goto unlock;
	}
	if (dev->flags & ATA_DFLAG_NO_UNLOAD) {
		rc = -EOPNOTSUPP;
		goto unlock;
	}

	link = dev->link;
	now = jiffies;
	if (ap->pflags & ATA_PFLAG_EH_IN_PROGRESS &&
	    link->eh_context.unloaded_mask & (1 << dev->devno) &&
	    time_after(dev->unpark_deadline, now))
		msecs = jiffies_to_msecs(dev->unpark_deadline - now);
	else
		msecs = 0;

unlock:
	spin_unlock_irq(ap->lock);

	return rc ? rc : snprintf(buf, 20, "%u\n", msecs);
}
