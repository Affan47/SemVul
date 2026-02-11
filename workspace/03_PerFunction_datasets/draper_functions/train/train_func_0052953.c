soc_camera_free_user_formats(struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);

	if (ici->ops->put_formats)
		ici->ops->put_formats(icd);
	icd->current_fmt = NULL;
	icd->num_user_formats = 0;
	vfree(icd->user_formats);
	icd->user_formats = NULL;
}
