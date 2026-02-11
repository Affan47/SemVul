rproc_handle_vdev(struct rproc *rproc, struct fw_rsc_vdev *rsc,
							int offset, int avail)
{
	struct device *dev = &rproc->dev;
	struct rproc_vdev *rvdev;
	int i, ret;


	if (sizeof(*rsc) + rsc->num_of_vrings * sizeof(struct fw_rsc_vdev_vring)
			+ rsc->config_len > avail) {
		dev_err(dev, "vdev rsc is truncated\n");
		return -EINVAL;
	}


	if (rsc->reserved[0] || rsc->reserved[1]) {
		dev_err(dev, "vdev rsc has non zero reserved bytes\n");
		return -EINVAL;
	}

	dev_dbg(dev, "vdev rsc: id %d, dfeatures %x, cfg len %d, %d vrings\n",
		rsc->id, rsc->dfeatures, rsc->config_len, rsc->num_of_vrings);


	if (rsc->num_of_vrings > ARRAY_SIZE(rvdev->vring)) {
		dev_err(dev, "too many vrings: %d\n", rsc->num_of_vrings);
		return -EINVAL;
	}

	rvdev = kzalloc(sizeof(struct rproc_vdev), GFP_KERNEL);
	if (!rvdev)
		return -ENOMEM;

	rvdev->rproc = rproc;


	for (i = 0; i < rsc->num_of_vrings; i++) {
		ret = rproc_parse_vring(rvdev, rsc, i);
		if (ret)
			goto free_rvdev;
	}


	rvdev->rsc_offset = offset;

	list_add_tail(&rvdev->node, &rproc->rvdevs);


	ret = rproc_add_virtio_dev(rvdev, rsc->id);
	if (ret)
		goto remove_rvdev;

	return 0;

remove_rvdev:
	list_del(&rvdev->node);
free_rvdev:
	kfree(rvdev);
	return ret;
}
