host_show_hp_ssd_smart_path_enabled(struct device *dev,
	     struct device_attribute *attr, char *buf)
{
	struct ctlr_info *h;
	struct scsi_device *sdev;
	struct hpsa_scsi_dev_t *hdev;
	unsigned long flags;
	int offload_enabled;

	sdev = to_scsi_device(dev);
	h = sdev_to_hba(sdev);
	spin_lock_irqsave(&h->lock, flags);
	hdev = sdev->hostdata;
	if (!hdev) {
		spin_unlock_irqrestore(&h->lock, flags);
		return -ENODEV;
	}
	offload_enabled = hdev->offload_enabled;
	spin_unlock_irqrestore(&h->lock, flags);
	return snprintf(buf, 20, "%d\n", offload_enabled);
}
