i915_gem_dmabuf_vunmap(struct dma_buf *dma_buf, void *vaddr)
{
	struct drm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	struct drm_device *dev = obj->base.dev;

	mutex_lock(&dev->struct_mutex);
	if (--obj->vmapping_count == 0) {
		vunmap(obj->dma_buf_vmapping);
		obj->dma_buf_vmapping = NULL;

		i915_gem_object_unpin_pages(obj);
	}
	mutex_unlock(&dev->struct_mutex);
}
