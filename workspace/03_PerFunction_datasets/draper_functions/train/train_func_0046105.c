au0828_v4l2_close(struct file *filp)
{
	int ret;
	struct au0828_dev *dev = video_drvdata(filp);
	struct video_device *vdev = video_devdata(filp);

	dprintk(1,
		"%s called std_set %d dev_state %ld stream users %d users %d\n",
		__func__, dev->std_set_in_tuner_core, dev->dev_state,
		dev->streaming_users, dev->users);

	mutex_lock(&dev->lock);
	if (vdev->vfl_type == VFL_TYPE_GRABBER && dev->vid_timeout_running) {

		dev->vid_timeout_running = 0;
		del_timer_sync(&dev->vid_timeout);
	} else if (vdev->vfl_type == VFL_TYPE_VBI &&
			dev->vbi_timeout_running) {

		dev->vbi_timeout_running = 0;
		del_timer_sync(&dev->vbi_timeout);
	}

	if (test_bit(DEV_DISCONNECTED, &dev->dev_state))
		goto end;

	if (dev->users == 1) {

		v4l2_device_call_all(&dev->v4l2_dev, 0, core, s_power, 0);
		dev->std_set_in_tuner_core = 0;


		ret = usb_set_interface(dev->usbdev, 0, 0);
		if (ret < 0)
			pr_info("Au0828 can't set alternate to 0!\n");
	}
end:
	_vb2_fop_release(filp, NULL);
	dev->users--;
	mutex_unlock(&dev->lock);
	return 0;
}
