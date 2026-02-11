cx88_dvb_bus_ctrl(struct dvb_frontend* fe, int acquire)
{
	struct cx8802_dev *dev= fe->dvb->priv;
	struct cx8802_driver *drv = NULL;
	int ret = 0;
	int fe_id;

	fe_id = vb2_dvb_find_frontend(&dev->frontends, fe);
	if (!fe_id) {
		printk(KERN_ERR "%s() No frontend found\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&dev->core->lock);
	drv = cx8802_get_driver(dev, CX88_MPEG_DVB);
	if (drv) {
		if (acquire){
			dev->frontends.active_fe_id = fe_id;
			ret = drv->request_acquire(drv);
		} else {
			ret = drv->request_release(drv);
			dev->frontends.active_fe_id = 0;
		}
	}
	mutex_unlock(&dev->core->lock);

	return ret;
}
