pfc_config(struct pcmcia_device *p_dev)
{
	unsigned int port = 0;
	struct serial_info *info = p_dev->priv;

	if ((p_dev->resource[1]->end != 0) &&
		(resource_size(p_dev->resource[1]) == 8)) {
		port = p_dev->resource[1]->start;
		info->slave = 1;
	} else if ((info->manfid == MANFID_OSITECH) &&
		(resource_size(p_dev->resource[0]) == 0x40)) {
		port = p_dev->resource[0]->start + 0x28;
		info->slave = 1;
	}
	if (info->slave)
		return setup_serial(p_dev, info, port, p_dev->irq);

	dev_warn(&p_dev->dev, "no usable port range found, giving up\n");
	return -ENODEV;
}
