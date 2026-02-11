multi_config_check(struct pcmcia_device *p_dev, void *priv_data)
{
	int *multi = priv_data;

	if (p_dev->resource[1]->end)
		return -EINVAL;


	if (p_dev->resource[0]->end <= 8)
		return -EINVAL;

	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	p_dev->resource[0]->end = *multi * 8;

	if (pcmcia_request_io(p_dev))
		return -ENODEV;
	return 0;
}
