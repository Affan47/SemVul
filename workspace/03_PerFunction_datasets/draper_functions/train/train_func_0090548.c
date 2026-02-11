au0828_restart_dvb_streaming(struct work_struct *work)
{
	struct au0828_dev *dev = container_of(work, struct au0828_dev,
					      restart_streaming);
	struct au0828_dvb *dvb = &dev->dvb;

	if (!dev->urb_streaming)
		return;

	dprintk(1, "Restarting streaming...!\n");

	mutex_lock(&dvb->lock);


	stop_urb_transfer(dev);
	au0828_stop_transport(dev, 1);


	au0828_start_transport(dev);
	start_urb_transfer(dev);

	mutex_unlock(&dvb->lock);
}
