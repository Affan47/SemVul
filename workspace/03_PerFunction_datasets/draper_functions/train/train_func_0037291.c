drm_gem_cma_free_object(struct drm_gem_object *gem_obj)
{
	struct drm_gem_cma_object *cma_obj;

	cma_obj = to_drm_gem_cma_obj(gem_obj);

	if (cma_obj->vaddr) {
		dma_free_writecombine(gem_obj->dev->dev, cma_obj->base.size,
				      cma_obj->vaddr, cma_obj->paddr);
	} else if (gem_obj->import_attach) {
		drm_prime_gem_destroy(gem_obj, cma_obj->sgt);
	}

	drm_gem_object_release(gem_obj);

	kfree(cma_obj);
}
