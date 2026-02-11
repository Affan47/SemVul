store_spi_transport_period(struct device *cdev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct scsi_target *starget = transport_class_to_starget(cdev);
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	struct spi_internal *i = to_spi_internal(shost->transportt);
	struct spi_transport_attrs *tp =
		(struct spi_transport_attrs *)&starget->starget_data;
	int period, retval;

	if (!i->f->set_period)
		return -EINVAL;

	retval = store_spi_transport_period_helper(cdev, buf, count, &period);

	if (period < tp->min_period)
		period = tp->min_period;

	i->f->set_period(starget, period);

	return retval;
}
