soc_camera_async_bound(struct v4l2_async_notifier *notifier,
				  struct v4l2_subdev *sd,
				  struct v4l2_async_subdev *asd)
{
	struct soc_camera_async_client *sasc = container_of(notifier,
					struct soc_camera_async_client, notifier);
	struct soc_camera_device *icd = platform_get_drvdata(sasc->pdev);

	if (asd == sasc->sensor && !WARN_ON(icd->control)) {
		struct i2c_client *client = v4l2_get_subdevdata(sd);


		if (client) {
			struct soc_camera_desc *sdesc = to_soc_camera_desc(icd);
			struct soc_camera_subdev_desc *ssdd =
				soc_camera_i2c_to_desc(client);
			if (ssdd) {
				memcpy(&sdesc->subdev_desc, ssdd,
				       sizeof(sdesc->subdev_desc));
				if (ssdd->reset)
					ssdd->reset(&client->dev);
			}

			icd->control = &client->dev;
		}
	}

	return 0;
}
