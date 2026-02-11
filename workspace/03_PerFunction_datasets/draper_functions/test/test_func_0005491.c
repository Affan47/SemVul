intel_rotate_fb_obj_pages(struct i915_ggtt_view *ggtt_view,
			  struct drm_i915_gem_object *obj)
{
	struct intel_rotation_info *rot_info = &ggtt_view->rotation_info;
	unsigned int size_pages = rot_info->size >> PAGE_SHIFT;
	unsigned int size_pages_uv;
	struct sg_page_iter sg_iter;
	unsigned long i;
	dma_addr_t *page_addr_list;
	struct sg_table *st;
	unsigned int uv_start_page;
	struct scatterlist *sg;
	int ret = -ENOMEM;


	page_addr_list = drm_malloc_ab(obj->base.size / PAGE_SIZE,
				       sizeof(dma_addr_t));
	if (!page_addr_list)
		return ERR_PTR(ret);


	if (rot_info->pixel_format == DRM_FORMAT_NV12)
		size_pages_uv = rot_info->size_uv >> PAGE_SHIFT;
	else
		size_pages_uv = 0;


	st = kmalloc(sizeof(*st), GFP_KERNEL);
	if (!st)
		goto err_st_alloc;

	ret = sg_alloc_table(st, size_pages + size_pages_uv, GFP_KERNEL);
	if (ret)
		goto err_sg_alloc;


	i = 0;
	for_each_sg_page(obj->pages->sgl, &sg_iter, obj->pages->nents, 0) {
		page_addr_list[i] = sg_page_iter_dma_address(&sg_iter);
		i++;
	}


	sg = rotate_pages(page_addr_list, 0,
		     rot_info->width_pages, rot_info->height_pages,
		     st, NULL);


	if (rot_info->pixel_format == DRM_FORMAT_NV12) {
		uv_start_page = size_pages;


		if (offset_in_page(rot_info->uv_offset))
			uv_start_page--;

		rot_info->uv_start_page = uv_start_page;

		rotate_pages(page_addr_list, uv_start_page,
			     rot_info->width_pages_uv,
			     rot_info->height_pages_uv,
			     st, sg);
	}

	DRM_DEBUG_KMS(
		      "Created rotated page mapping for object size %zu (pitch=%u, height=%u, pixel_format=0x%x, %ux%u tiles, %u pages (%u plane 0)).\n",
		      obj->base.size, rot_info->pitch, rot_info->height,
		      rot_info->pixel_format, rot_info->width_pages,
		      rot_info->height_pages, size_pages + size_pages_uv,
		      size_pages);

	drm_free_large(page_addr_list);

	return st;

err_sg_alloc:
	kfree(st);
err_st_alloc:
	drm_free_large(page_addr_list);

	DRM_DEBUG_KMS(
		      "Failed to create rotated mapping for object size %zu! (%d) (pitch=%u, height=%u, pixel_format=0x%x, %ux%u tiles, %u pages (%u plane 0))\n",
		      obj->base.size, ret, rot_info->pitch, rot_info->height,
		      rot_info->pixel_format, rot_info->width_pages,
		      rot_info->height_pages, size_pages + size_pages_uv,
		      size_pages);
	return ERR_PTR(ret);
}
