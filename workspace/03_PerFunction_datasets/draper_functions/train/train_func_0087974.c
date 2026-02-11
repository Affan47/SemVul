clear_mode(struct device *dev)
{
	if (dev->mode.fb_id)
		drmModeRmFB(dev->fd, dev->mode.fb_id);
	if (dev->mode.bo)
		bo_destroy(dev->mode.bo);
}
