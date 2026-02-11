init_status_page(struct intel_engine_cs *engine)
{
	struct drm_i915_gem_object *obj = engine->status_page.obj;

	if (obj == NULL) {
		unsigned flags;
		int ret;

		obj = i915_gem_alloc_object(engine->dev, 4096);
		if (obj == NULL) {
			DRM_ERROR("Failed to allocate status page\n");
			return -ENOMEM;
		}

		ret = i915_gem_object_set_cache_level(obj, I915_CACHE_LLC);
		if (ret)
			goto err_unref;

		flags = 0;
		if (!HAS_LLC(engine->dev))


			flags |= PIN_MAPPABLE;
		ret = i915_gem_obj_ggtt_pin(obj, 4096, flags);
		if (ret) {
err_unref:
			drm_gem_object_unreference(&obj->base);
			return ret;
		}

		engine->status_page.obj = obj;
	}

	engine->status_page.gfx_addr = i915_gem_obj_ggtt_offset(obj);
	engine->status_page.page_addr = kmap(sg_page(obj->pages->sgl));
	memset(engine->status_page.page_addr, 0, PAGE_SIZE);

	DRM_DEBUG_DRIVER("%s hws offset: 0x%08x\n",
			engine->name, engine->status_page.gfx_addr);

	return 0;
}
