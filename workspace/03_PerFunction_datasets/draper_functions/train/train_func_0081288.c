v4l2_ctrl_log_status(struct file *file, void *fh)
{
	struct video_device *vfd = video_devdata(file);
	struct v4l2_fh *vfh = file->private_data;

	if (test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) && vfd->v4l2_dev)
		v4l2_ctrl_handler_log_status(vfh->ctrl_handler,
			vfd->v4l2_dev->name);
	return 0;
}
