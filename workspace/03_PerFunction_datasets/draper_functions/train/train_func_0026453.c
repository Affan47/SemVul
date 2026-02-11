xvip_graph_notify_bound(struct v4l2_async_notifier *notifier,
				   struct v4l2_subdev *subdev,
				   struct v4l2_async_subdev *asd)
{
	struct xvip_composite_device *xdev =
		container_of(notifier, struct xvip_composite_device, notifier);
	struct xvip_graph_entity *entity;


	list_for_each_entry(entity, &xdev->entities, list) {
		if (entity->node != subdev->dev->of_node)
			continue;

		if (entity->subdev) {
			dev_err(xdev->dev, "duplicate subdev for node %s\n",
				entity->node->full_name);
			return -EINVAL;
		}

		dev_dbg(xdev->dev, "subdev %s bound\n", subdev->name);
		entity->entity = &subdev->entity;
		entity->subdev = subdev;
		return 0;
	}

	dev_err(xdev->dev, "no entity for subdev %s\n", subdev->name);
	return -EINVAL;
}
