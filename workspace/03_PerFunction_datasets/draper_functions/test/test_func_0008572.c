csi2_subdev(struct sh_mobile_ceu_dev *pcdev,
				       struct soc_camera_device *icd)
{
	struct v4l2_subdev *sd = pcdev->csi2_sd;

	return sd && sd->grp_id == soc_camera_grp_id(icd) ? sd : NULL;
}
