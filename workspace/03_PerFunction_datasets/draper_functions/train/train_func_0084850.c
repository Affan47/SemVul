vmw_cotable_resize(struct vmw_resource *res, size_t new_size)
{
	struct vmw_private *dev_priv = res->dev_priv;
	struct vmw_cotable *vcotbl = vmw_cotable(res);
	struct vmw_dma_buffer *buf, *old_buf = res->backup;
	struct ttm_buffer_object *bo, *old_bo = &res->backup->base;
	size_t old_size = res->backup_size;
	size_t old_size_read_back = vcotbl->size_read_back;
	size_t cur_size_read_back;
	struct ttm_bo_kmap_obj old_map, new_map;
	int ret;
	size_t i;

	ret = vmw_cotable_readback(res);
	if (ret)
		return ret;

	cur_size_read_back = vcotbl->size_read_back;
	vcotbl->size_read_back = old_size_read_back;


	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = vmw_dmabuf_init(dev_priv, buf, new_size, &vmw_mob_ne_placement,
			      true, vmw_dmabuf_bo_free);
	if (ret) {
		DRM_ERROR("Failed initializing new cotable MOB.\n");
		return ret;
	}

	bo = &buf->base;
	WARN_ON_ONCE(ttm_bo_reserve(bo, false, true, false, NULL));

	ret = ttm_bo_wait(old_bo, false, false, false);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Failed waiting for cotable unbind.\n");
		goto out_wait;
	}


	for (i = 0; i < old_bo->num_pages; ++i) {
		bool dummy;

		ret = ttm_bo_kmap(old_bo, i, 1, &old_map);
		if (unlikely(ret != 0)) {
			DRM_ERROR("Failed mapping old COTable on resize.\n");
			goto out_wait;
		}
		ret = ttm_bo_kmap(bo, i, 1, &new_map);
		if (unlikely(ret != 0)) {
			DRM_ERROR("Failed mapping new COTable on resize.\n");
			goto out_map_new;
		}
		memcpy(ttm_kmap_obj_virtual(&new_map, &dummy),
		       ttm_kmap_obj_virtual(&old_map, &dummy),
		       PAGE_SIZE);
		ttm_bo_kunmap(&new_map);
		ttm_bo_kunmap(&old_map);
	}


	ret = ttm_bo_validate(bo, &vmw_mob_placement, false, false);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Failed validating new COTable backup buffer.\n");
		goto out_wait;
	}

	res->backup = buf;
	res->backup_size = new_size;
	vcotbl->size_read_back = cur_size_read_back;


	ret = vmw_cotable_unscrub(res);
	if (ret) {
		DRM_ERROR("Failed switching COTable backup buffer.\n");
		res->backup = old_buf;
		res->backup_size = old_size;
		vcotbl->size_read_back = old_size_read_back;
		goto out_wait;
	}


	list_del(&res->mob_head);
	list_add_tail(&res->mob_head, &buf->res_list);
	vmw_dmabuf_unreference(&old_buf);
	res->id = vcotbl->type;

	return 0;

out_map_new:
	ttm_bo_kunmap(&old_map);
out_wait:
	ttm_bo_unreserve(bo);
	vmw_dmabuf_unreference(&buf);

	return ret;
}
