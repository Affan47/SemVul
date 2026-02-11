proc_print_scsidevice(struct device *dev, void *data)
{
	struct scsi_device *sdev;
	struct seq_file *s = data;
	int i;

	if (!scsi_is_sdev_device(dev))
		goto out;

	sdev = to_scsi_device(dev);
	seq_printf(s,
		"Host: scsi%d Channel: %02d Id: %02d Lun: %02llu\n  Vendor: ",
		sdev->host->host_no, sdev->channel, sdev->id, sdev->lun);
	for (i = 0; i < 8; i++) {
		if (sdev->vendor[i] >= 0x20)
			seq_putc(s, sdev->vendor[i]);
		else
			seq_putc(s, ' ');
	}

	seq_puts(s, " Model: ");
	for (i = 0; i < 16; i++) {
		if (sdev->model[i] >= 0x20)
			seq_putc(s, sdev->model[i]);
		else
			seq_putc(s, ' ');
	}

	seq_puts(s, " Rev: ");
	for (i = 0; i < 4; i++) {
		if (sdev->rev[i] >= 0x20)
			seq_putc(s, sdev->rev[i]);
		else
			seq_putc(s, ' ');
	}

	seq_putc(s, '\n');

	seq_printf(s, "  Type:   %s ", scsi_device_type(sdev->type));
	seq_printf(s, "               ANSI  SCSI revision: %02x",
			sdev->scsi_level - (sdev->scsi_level > 1));
	if (sdev->scsi_level == 2)
		seq_puts(s, " CCS\n");
	else
		seq_putc(s, '\n');

out:
	return 0;
}
