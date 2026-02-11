dev_deactivate(struct fp_img_dev *imgdev)
{
	struct fp_driver *drv = imgdev->dev->drv;
	struct fp_img_driver *imgdrv = fpi_driver_to_img_driver(drv);

	if (!imgdrv->deactivate)
		return;
	return imgdrv->deactivate(imgdev);
}
