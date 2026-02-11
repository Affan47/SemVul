xvip_graph_notify_complete(struct v4l2_async_notifier *notifier)
{
	struct xvip_composite_device *xdev =
		container_of(notifier, struct xvip_composite_device, notifier);
	struct xvip_graph_entity *entity;
	int ret;

	dev_dbg(xdev->dev, "notify complete, all subdevs registered\n");


	list_for_each_entry(entity, &xdev->entities, list) {
		ret = xvip_graph_build_one(xdev, entity);
		if (ret < 0)
			return ret;
	}


	ret = xvip_graph_build_dma(xdev);
	if (ret < 0)
		return ret;

	ret = v4l2_device_register_subdev_nodes(&xdev->v4l2_dev);
	if (ret < 0)
		dev_err(xdev->dev, "failed to register subdev nodes\n");

	return ret;
}
