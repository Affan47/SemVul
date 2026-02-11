sirdev_set_dtr_rts(struct sir_dev *dev, int dtr, int rts)
{
	int ret = -ENXIO;
	if (dev->drv->set_dtr_rts)
		ret =  dev->drv->set_dtr_rts(dev, dtr, rts);
	return ret;
}
