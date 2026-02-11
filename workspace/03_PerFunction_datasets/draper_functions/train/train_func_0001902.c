ivtv_v4l2_open(struct file *filp)
{
	struct video_device *vdev = video_devdata(filp);
	int res;

	if (mutex_lock_interruptible(vdev->lock))
		return -ERESTARTSYS;
	res = ivtv_open(filp);
	mutex_unlock(vdev->lock);
	return res;
}
