virtio_finalize_features(struct virtio_device *dev)
{
	int ret = dev->config->finalize_features(dev);
	unsigned status;

	if (ret)
		return ret;

	if (!virtio_has_feature(dev, VIRTIO_F_VERSION_1))
		return 0;

	add_status(dev, VIRTIO_CONFIG_S_FEATURES_OK);
	status = dev->config->get_status(dev);
	if (!(status & VIRTIO_CONFIG_S_FEATURES_OK)) {
		dev_err(&dev->dev, "virtio: device refuses features: %x\n",
			status);
		return -ENODEV;
	}
	return 0;
}
