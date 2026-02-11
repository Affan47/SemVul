amdgpu_mm_dump_table(struct seq_file *m, void *data)
{
	struct drm_info_node *node = (struct drm_info_node *)m->private;
	unsigned ttm_pl = *(int *)node->info_ent->data;
	struct drm_device *dev = node->minor->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct drm_mm *mm = (struct drm_mm *)adev->mman.bdev.man[ttm_pl].priv;
	int ret;
	struct ttm_bo_global *glob = adev->mman.bdev.glob;

	spin_lock(&glob->lru_lock);
	ret = drm_mm_dump_table(m, mm);
	spin_unlock(&glob->lru_lock);
	if (ttm_pl == TTM_PL_VRAM)
		seq_printf(m, "man size:%llu pages, ram usage:%lluMB, vis usage:%lluMB\n",
			   adev->mman.bdev.man[ttm_pl].size,
			   (u64)atomic64_read(&adev->vram_usage) >> 20,
			   (u64)atomic64_read(&adev->vram_vis_usage) >> 20);
	return ret;
}
