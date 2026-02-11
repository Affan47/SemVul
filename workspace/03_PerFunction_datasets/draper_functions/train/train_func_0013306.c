gma_power_init(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;


	dev_priv->apm_base = dev_priv->apm_reg & 0xffff;
	dev_priv->ospm_base &= 0xffff;

	dev_priv->display_power = true;
	dev_priv->display_count = 0;
	dev_priv->suspended = false;
	spin_lock_init(&power_ctrl_lock);
	mutex_init(&power_mutex);

	if (dev_priv->ops->init_pm)
		dev_priv->ops->init_pm(dev);
}
