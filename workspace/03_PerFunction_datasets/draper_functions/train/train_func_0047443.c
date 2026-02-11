rproc_add_virtio_dev(struct rproc_vdev *rvdev, int id)
{
	struct rproc *rproc = rvdev->rproc;
	struct device *dev = &rproc->dev;
	struct virtio_device *vdev = &rvdev->vdev;
	int ret;

	vdev->id.device	= id,
	vdev->config = &rproc_virtio_config_ops,
	vdev->dev.parent = dev;
	vdev->dev.release = rproc_vdev_release;


	get_device(&rproc->dev);

	ret = register_virtio_device(vdev);
	if (ret) {
		put_device(&rproc->dev);
		dev_err(dev, "failed to register vdev: %d\n", ret);
		goto out;
	}

	dev_info(dev, "registered %s (type %d)\n", dev_name(&vdev->dev), id);

out:
	return ret;
}
