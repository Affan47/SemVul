vmw_kms_ldu_close_display(struct vmw_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;

	if (!dev_priv->ldu_priv)
		return -ENOSYS;

	drm_vblank_cleanup(dev);

	BUG_ON(!list_empty(&dev_priv->ldu_priv->active));

	kfree(dev_priv->ldu_priv);

	return 0;
}
