au0828_dvb_stop_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux = feed->demux;
	struct au0828_dev *dev = (struct au0828_dev *) demux->priv;
	struct au0828_dvb *dvb = &dev->dvb;
	int ret = 0;

	dprintk(1, "%s()\n", __func__);

	if (dvb->frontend) {
		cancel_work_sync(&dev->restart_streaming);

		mutex_lock(&dvb->lock);
		dvb->stop_count++;
		dprintk(1, "%s(), start_count: %d, stop_count: %d\n", __func__,
			dvb->start_count, dvb->stop_count);
		if (dvb->feeding > 0) {
			dvb->feeding--;
			if (dvb->feeding == 0) {

				ret = stop_urb_transfer(dev);
				au0828_stop_transport(dev, 0);
			}
		}
		mutex_unlock(&dvb->lock);
	}

	return ret;
}
