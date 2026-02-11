scsi_log_print_sense_hdr(const struct scsi_device *sdev, const char *name,
			 int tag, const struct scsi_sense_hdr *sshdr)
{
	char *logbuf;
	size_t off, logbuf_len;

	logbuf = scsi_log_reserve_buffer(&logbuf_len);
	if (!logbuf)
		return;
	off = sdev_format_header(logbuf, logbuf_len, name, tag);
	off += scsi_format_sense_hdr(logbuf + off, logbuf_len - off, sshdr);
	dev_printk(KERN_INFO, &sdev->sdev_gendev, "%s", logbuf);
	scsi_log_release_buffer(logbuf);

	logbuf = scsi_log_reserve_buffer(&logbuf_len);
	if (!logbuf)
		return;
	off = sdev_format_header(logbuf, logbuf_len, name, tag);
	off += scsi_format_extd_sense(logbuf + off, logbuf_len - off,
				      sshdr->asc, sshdr->ascq);
	dev_printk(KERN_INFO, &sdev->sdev_gendev, "%s", logbuf);
	scsi_log_release_buffer(logbuf);
}
