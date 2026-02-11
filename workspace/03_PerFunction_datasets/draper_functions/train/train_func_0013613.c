scif_peer_initialize_device(struct scif_dev *scifdev)
{
	struct scif_peer_dev *spdev;
	int ret;

	spdev = kzalloc(sizeof(*spdev), GFP_KERNEL);
	if (!spdev) {
		ret = -ENOMEM;
		goto err;
	}

	spdev->dev.parent = scifdev->sdev->dev.parent;
	spdev->dev.release = scif_peer_release_dev;
	spdev->dnode = scifdev->node;
	spdev->dev.bus = &scif_peer_bus;
	dev_set_name(&spdev->dev, "scif_peer-dev%u", spdev->dnode);

	device_initialize(&spdev->dev);
	get_device(&spdev->dev);
	rcu_assign_pointer(scifdev->spdev, spdev);

	mutex_lock(&scif_info.conflock);
	scif_info.total++;
	scif_info.maxid = max_t(u32, spdev->dnode, scif_info.maxid);
	mutex_unlock(&scif_info.conflock);
	return 0;
err:
	dev_err(&scifdev->sdev->dev,
		"dnode %d: initialize_device rc %d\n", scifdev->node, ret);
	return ret;
}
