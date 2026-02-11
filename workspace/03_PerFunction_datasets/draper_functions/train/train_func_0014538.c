vmw_execbuf_unpin_panic(struct vmw_private *dev_priv)
{
	DRM_ERROR("Can't unpin query buffer. Trying to recover.\n");

	(void) vmw_fallback_wait(dev_priv, false, true, 0, false, 10*HZ);
	vmw_bo_pin_reserved(dev_priv->pinned_bo, false);
	if (dev_priv->dummy_query_bo_pinned) {
		vmw_bo_pin_reserved(dev_priv->dummy_query_bo, false);
		dev_priv->dummy_query_bo_pinned = false;
	}
}
