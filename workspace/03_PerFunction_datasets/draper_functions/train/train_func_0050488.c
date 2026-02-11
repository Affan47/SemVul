subdev_notifier_bound(struct v4l2_async_notifier *notifier,
				 struct v4l2_subdev *subdev,
				 struct v4l2_async_subdev *asd)
{
	struct fimc_md *fmd = notifier_to_fimc_md(notifier);
	struct fimc_sensor_info *si = NULL;
	int i;


	for (i = 0; i < ARRAY_SIZE(fmd->sensor); i++)
		if (fmd->sensor[i].asd.match.of.node == subdev->dev->of_node)
			si = &fmd->sensor[i];

	if (si == NULL)
		return -EINVAL;

	v4l2_set_subdev_hostdata(subdev, &si->pdata);

	if (si->pdata.fimc_bus_type == FIMC_BUS_TYPE_ISP_WRITEBACK)
		subdev->grp_id = GRP_ID_FIMC_IS_SENSOR;
	else
		subdev->grp_id = GRP_ID_SENSOR;

	si->subdev = subdev;

	v4l2_info(&fmd->v4l2_dev, "Registered sensor subdevice: %s (%d)\n",
		  subdev->name, fmd->num_sensors);

	fmd->num_sensors++;

	return 0;
}
