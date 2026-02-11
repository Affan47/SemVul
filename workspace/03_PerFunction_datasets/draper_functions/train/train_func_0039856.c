soc_camera_async_complete(struct v4l2_async_notifier *notifier)
{
	struct soc_camera_async_client *sasc = container_of(notifier,
					struct soc_camera_async_client, notifier);
	struct soc_camera_device *icd = platform_get_drvdata(sasc->pdev);

	if (to_soc_camera_control(icd)) {
		struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
		int ret;

		mutex_lock(&list_lock);
		ret = soc_camera_probe(ici, icd);
		mutex_unlock(&list_lock);
		if (ret < 0)
			return ret;
	}

	return 0;
}
