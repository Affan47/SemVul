frame_ready(struct gspca_dev *gspca_dev, struct file *file,
			enum v4l2_memory memory)
{
	int ret;

	if (mutex_lock_interruptible(&gspca_dev->queue_lock))
		return -ERESTARTSYS;
	ret = frame_ready_nolock(gspca_dev, file, memory);
	mutex_unlock(&gspca_dev->queue_lock);
	return ret;
}
