vidioc_log_status(struct file *file, void *fh)
{
	struct video_device *vdev = video_devdata(file);

	dprintk(1, "%s called\n", __func__);

	v4l2_ctrl_log_status(file, fh);
	v4l2_device_call_all(vdev->v4l2_dev, 0, core, log_status);
	return 0;
}
