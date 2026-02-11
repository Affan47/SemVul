soc_camera_remove(struct soc_camera_device *icd)
{
	struct soc_camera_desc *sdesc = to_soc_camera_desc(icd);
	struct video_device *vdev = icd->vdev;

	v4l2_ctrl_handler_free(&icd->ctrl_handler);
	if (vdev) {
		video_unregister_device(vdev);
		icd->vdev = NULL;
	}

	if (sdesc->host_desc.board_info) {
		soc_camera_i2c_free(icd);
	} else {
		struct device *dev = to_soc_camera_control(icd);
		struct device_driver *drv = dev ? dev->driver : NULL;
		if (drv) {
			sdesc->host_desc.del_device(icd);
			module_put(drv->owner);
		}
	}

	if (icd->num_user_formats)
		soc_camera_free_user_formats(icd);

	if (icd->clk) {

		v4l2_clk_unregister(icd->clk);
		icd->clk = NULL;
	}

	if (icd->sasc)
		platform_device_unregister(icd->sasc->pdev);

	return 0;
}
