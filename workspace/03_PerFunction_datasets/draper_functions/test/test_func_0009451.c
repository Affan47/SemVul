mptspi_slave_configure(struct scsi_device *sdev)
{
	struct _MPT_SCSI_HOST *hd = shost_priv(sdev->host);
	VirtTarget *vtarget = scsi_target(sdev)->hostdata;
	int ret;

	mptspi_initTarget(hd, vtarget, sdev);

	ret = mptscsih_slave_configure(sdev);

	if (ret)
		return ret;

	ddvprintk(hd->ioc, printk(MYIOC_s_DEBUG_FMT "id=%d min_period=0x%02x"
		" max_offset=0x%02x max_width=%d\n", hd->ioc->name,
		sdev->id, spi_min_period(scsi_target(sdev)),
		spi_max_offset(scsi_target(sdev)),
		spi_max_width(scsi_target(sdev))));

	if ((sdev->channel == 1 ||
	     !(mptspi_is_raid(hd, sdev->id))) &&
	    !spi_initial_dv(sdev->sdev_target))
		mptspi_dv_device(hd, sdev);

	return 0;
}
