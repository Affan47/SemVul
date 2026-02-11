vmw_release_device_early(struct vmw_private *dev_priv)
{


	BUG_ON(dev_priv->pinned_bo != NULL);

	vmw_dmabuf_unreference(&dev_priv->dummy_query_bo);
	if (dev_priv->cman)
		vmw_cmdbuf_remove_pool(dev_priv->cman);

	if (dev_priv->has_mob) {
		ttm_bo_evict_mm(&dev_priv->bdev, VMW_PL_MOB);
		vmw_otables_takedown(dev_priv);
	}
}
