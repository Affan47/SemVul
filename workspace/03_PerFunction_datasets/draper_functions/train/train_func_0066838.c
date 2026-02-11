spi_device_match(struct attribute_container *cont,
			    struct device *dev)
{
	struct scsi_device *sdev;
	struct Scsi_Host *shost;
	struct spi_internal *i;

	if (!scsi_is_sdev_device(dev))
		return 0;

	sdev = to_scsi_device(dev);
	shost = sdev->host;
	if (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &spi_host_class.class)
		return 0;


	i = to_spi_internal(shost->transportt);
	if (i->f->deny_binding && i->f->deny_binding(sdev->sdev_target))
		return 0;
	return 1;
}
