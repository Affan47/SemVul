vmwgfx_pm_notifier(struct notifier_block *nb, unsigned long val,
			      void *ptr)
{
	struct vmw_private *dev_priv =
		container_of(nb, struct vmw_private, pm_nb);

	switch (val) {
	case PM_HIBERNATION_PREPARE:
		if (dev_priv->enable_fb)
			vmw_fb_off(dev_priv);
		ttm_suspend_lock(&dev_priv->reservation_sem);


		vmw_execbuf_release_pinned_bo(dev_priv);
		vmw_resource_evict_all(dev_priv);
		vmw_release_device_early(dev_priv);
		ttm_bo_swapout_all(&dev_priv->bdev);
		vmw_fence_fifo_down(dev_priv->fman);
		break;
	case PM_POST_HIBERNATION:
	case PM_POST_RESTORE:
		vmw_fence_fifo_up(dev_priv->fman);
		ttm_suspend_unlock(&dev_priv->reservation_sem);
		if (dev_priv->enable_fb)
			vmw_fb_on(dev_priv);
		break;
	case PM_RESTORE_PREPARE:
		break;
	default:
		break;
	}
	return 0;
}
