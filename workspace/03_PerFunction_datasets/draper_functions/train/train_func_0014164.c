vidioc_log_status(struct file *file, void *fh)
{
	struct vivid_dev *dev = video_drvdata(file);
	struct video_device *vdev = video_devdata(file);

	v4l2_ctrl_log_status(file, fh);
	if (vdev->vfl_dir == VFL_DIR_RX && vdev->vfl_type == VFL_TYPE_GRABBER)
		tpg_log_status(&dev->tpg);
	return 0;
}
