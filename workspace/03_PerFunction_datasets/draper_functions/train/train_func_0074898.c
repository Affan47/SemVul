soc_camera_video_start(struct soc_camera_device *icd)
{
	const struct device_type *type = icd->vdev->dev.type;
	int ret;

	if (!icd->parent)
		return -ENODEV;

	video_set_drvdata(icd->vdev, icd);
	if (icd->vdev->tvnorms == 0) {

		v4l2_disable_ioctl(icd->vdev, VIDIOC_G_STD);
		v4l2_disable_ioctl(icd->vdev, VIDIOC_S_STD);
		v4l2_disable_ioctl(icd->vdev, VIDIOC_ENUMSTD);
	}
	ret = video_register_device(icd->vdev, VFL_TYPE_GRABBER, -1);
	if (ret < 0) {
		dev_err(icd->pdev, "video_register_device failed: %d\n", ret);
		return ret;
	}


	icd->vdev->dev.type = type;

	return 0;
}
