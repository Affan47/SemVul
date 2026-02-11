psb_gtt_pin(struct gtt_range *gt)
{
	int ret = 0;
	struct drm_device *dev = gt->gem.dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	u32 gpu_base = dev_priv->gtt.gatt_start;

	mutex_lock(&dev_priv->gtt_mutex);

	if (gt->in_gart == 0 && gt->stolen == 0) {
		ret = psb_gtt_attach_pages(gt);
		if (ret < 0)
			goto out;
		ret = psb_gtt_insert(dev, gt, 0);
		if (ret < 0) {
			psb_gtt_detach_pages(gt);
			goto out;
		}
		psb_mmu_insert_pages(psb_mmu_get_default_pd(dev_priv->mmu),
				     gt->pages, (gpu_base + gt->offset),
				     gt->npage, 0, 0, PSB_MMU_CACHED_MEMORY);
	}
	gt->in_gart++;
out:
	mutex_unlock(&dev_priv->gtt_mutex);
	return ret;
}
