hackrf_querycap(struct file *file, void *fh,
		struct v4l2_capability *cap)
{
	struct hackrf_dev *dev = video_drvdata(file);
	struct usb_interface *intf = dev->intf;
	struct video_device *vdev = video_devdata(file);

	dev_dbg(&intf->dev, "\n");

	if (vdev->vfl_dir == VFL_DIR_RX)
		cap->device_caps = V4L2_CAP_SDR_CAPTURE | V4L2_CAP_TUNER |
				   V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;

	else
		cap->device_caps = V4L2_CAP_SDR_OUTPUT | V4L2_CAP_MODULATOR |
				   V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;

	cap->capabilities = V4L2_CAP_SDR_CAPTURE | V4L2_CAP_TUNER |
			    V4L2_CAP_SDR_OUTPUT | V4L2_CAP_MODULATOR |
			    V4L2_CAP_STREAMING | V4L2_CAP_READWRITE |
			    V4L2_CAP_DEVICE_CAPS;
	strlcpy(cap->driver, KBUILD_MODNAME, sizeof(cap->driver));
	strlcpy(cap->card, dev->rx_vdev.name, sizeof(cap->card));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));

	return 0;
}
