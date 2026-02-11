i915_gem_object_pin_map(struct drm_i915_gem_object *obj)
{
	int ret;

	lockdep_assert_held(&obj->base.dev->struct_mutex);

	ret = i915_gem_object_get_pages(obj);
	if (ret)
		return ERR_PTR(ret);

	i915_gem_object_pin_pages(obj);

	if (obj->mapping == NULL) {
		struct page **pages;

		pages = NULL;
		if (obj->base.size == PAGE_SIZE)
			obj->mapping = kmap(sg_page(obj->pages->sgl));
		else
			pages = drm_malloc_gfp(obj->base.size >> PAGE_SHIFT,
					       sizeof(*pages),
					       GFP_TEMPORARY);
		if (pages != NULL) {
			struct sg_page_iter sg_iter;
			int n;

			n = 0;
			for_each_sg_page(obj->pages->sgl, &sg_iter,
					 obj->pages->nents, 0)
				pages[n++] = sg_page_iter_page(&sg_iter);

			obj->mapping = vmap(pages, n, 0, PAGE_KERNEL);
			drm_free_large(pages);
		}
		if (obj->mapping == NULL) {
			i915_gem_object_unpin_pages(obj);
			return ERR_PTR(-ENOMEM);
		}
	}

	return obj->mapping;
}
