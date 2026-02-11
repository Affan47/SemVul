dvb_ca_en50221_io_release(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct dvb_ca_private *ca = dvbdev->priv;
	int err;

	dprintk("%s\n", __func__);


	ca->open = 0;
	dvb_ca_en50221_thread_update_delay(ca);

	err = dvb_generic_release(inode, file);

	module_put(ca->pub->owner);

	return err;
}
