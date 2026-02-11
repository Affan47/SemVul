via_create_subdev(struct viafb_dev *vdev,
			     struct viafb_subdev_info *info)
{
	int ret;

	info->platdev = platform_device_alloc(info->name, -1);
	if (!info->platdev) {
		dev_err(&vdev->pdev->dev, "Unable to allocate pdev %s\n",
			info->name);
		return -ENOMEM;
	}
	info->platdev->dev.parent = &vdev->pdev->dev;
	info->platdev->dev.platform_data = vdev;
	ret = platform_device_add(info->platdev);
	if (ret) {
		dev_err(&vdev->pdev->dev, "Unable to add pdev %s\n",
				info->name);
		platform_device_put(info->platdev);
		info->platdev = NULL;
	}
	return ret;
}
