drm_bridge_attach(struct drm_device *dev, struct drm_bridge *bridge)
{
	if (!dev || !bridge)
		return -EINVAL;

	if (bridge->dev)
		return -EBUSY;

	bridge->dev = dev;

	if (bridge->funcs->attach)
		return bridge->funcs->attach(bridge);

	return 0;
}
