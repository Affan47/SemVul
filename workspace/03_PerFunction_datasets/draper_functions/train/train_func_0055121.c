dvb_demux_release(struct inode *inode, struct file *file)
{
	struct dmxdev_filter *dmxdevfilter = file->private_data;
	struct dmxdev *dmxdev = dmxdevfilter->dev;

	int ret;

	ret = dvb_dmxdev_filter_free(dmxdev, dmxdevfilter);

	mutex_lock(&dmxdev->mutex);
	dmxdev->dvbdev->users--;
	if(dmxdev->dvbdev->users==1 && dmxdev->exit==1) {
		mutex_unlock(&dmxdev->mutex);
		wake_up(&dmxdev->dvbdev->wait_queue);
	} else
		mutex_unlock(&dmxdev->mutex);

	return ret;
}
