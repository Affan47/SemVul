sh_mobile_ceu_remove_device(struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	struct v4l2_subdev *csi2_sd = find_csi2(pcdev);

	dev_info(icd->parent,
		 "SuperH Mobile CEU driver detached from camera %d\n",
		 icd->devnum);

	v4l2_subdev_call(csi2_sd, core, s_power, 0);
}
