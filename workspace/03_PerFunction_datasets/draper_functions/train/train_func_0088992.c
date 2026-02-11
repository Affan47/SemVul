vgem_gem_free_object(struct drm_gem_object *obj)
{
	struct drm_vgem_gem_object *vgem_obj = to_vgem_bo(obj);

	drm_gem_free_mmap_offset(obj);

	if (vgem_obj->use_dma_buf && obj->dma_buf) {
		dma_buf_put(obj->dma_buf);
		obj->dma_buf = NULL;
	}

	drm_gem_object_release(obj);

	if (vgem_obj->pages)
		vgem_gem_put_pages(vgem_obj);

	vgem_obj->pages = NULL;

	kfree(vgem_obj);
}
