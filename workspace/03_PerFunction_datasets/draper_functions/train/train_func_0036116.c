bcm2048_vidioc_s_ctrl(struct file *file, void *priv,
		struct v4l2_control *ctrl)
{
	struct bcm2048_device *bdev = video_get_drvdata(video_devdata(file));
	int err = 0;

	if (!bdev)
		return -ENODEV;

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		if (ctrl->value) {
			if (bdev->power_state) {
				err = bcm2048_set_mute(bdev, ctrl->value);
				err |= bcm2048_deinit(bdev);
			}
		} else {
			if (!bdev->power_state) {
				err = bcm2048_init(bdev);
				err |= bcm2048_set_mute(bdev, ctrl->value);
			}
		}
		break;
	}

	return err;
}
