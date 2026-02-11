try_to_bring_up_master(struct master *master,
	struct component *component)
{
	int ret;

	if (master->bound)
		return 0;


	if (find_components(master)) {

		ret = 0;
		goto out;
	}

	if (component && component->master != master) {
		ret = 0;
		goto out;
	}

	if (!devres_open_group(master->dev, NULL, GFP_KERNEL)) {
		ret = -ENOMEM;
		goto out;
	}


	ret = master->ops->bind(master->dev);
	if (ret < 0) {
		devres_release_group(master->dev, NULL);
		dev_info(master->dev, "master bind failed: %d\n", ret);
		goto out;
	}

	master->bound = true;
	return 1;

out:
	master_remove_components(master);

	return ret;
}
