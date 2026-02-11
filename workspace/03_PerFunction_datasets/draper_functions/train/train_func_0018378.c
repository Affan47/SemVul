vmw_compat_shader_add(struct vmw_private *dev_priv,
			  struct vmw_cmdbuf_res_manager *man,
			  u32 user_key, const void *bytecode,
			  SVGA3dShaderType shader_type,
			  size_t size,
			  struct list_head *list)
{
	struct vmw_dma_buffer *buf;
	struct ttm_bo_kmap_obj map;
	bool is_iomem;
	int ret;
	struct vmw_resource *res;

	if (!vmw_shader_id_ok(user_key, shader_type))
		return -EINVAL;


	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (unlikely(buf == NULL))
		return -ENOMEM;

	ret = vmw_dmabuf_init(dev_priv, buf, size, &vmw_sys_ne_placement,
			      true, vmw_dmabuf_bo_free);
	if (unlikely(ret != 0))
		goto out;

	ret = ttm_bo_reserve(&buf->base, false, true, false, NULL);
	if (unlikely(ret != 0))
		goto no_reserve;


	ret = ttm_bo_kmap(&buf->base, 0, PAGE_ALIGN(size) >> PAGE_SHIFT,
			  &map);
	if (unlikely(ret != 0)) {
		ttm_bo_unreserve(&buf->base);
		goto no_reserve;
	}

	memcpy(ttm_kmap_obj_virtual(&map, &is_iomem), bytecode, size);
	WARN_ON(is_iomem);

	ttm_bo_kunmap(&map);
	ret = ttm_bo_validate(&buf->base, &vmw_sys_placement, false, true);
	WARN_ON(ret != 0);
	ttm_bo_unreserve(&buf->base);

	res = vmw_shader_alloc(dev_priv, buf, size, 0, shader_type);
	if (unlikely(ret != 0))
		goto no_reserve;

	ret = vmw_cmdbuf_res_add(man, vmw_cmdbuf_res_shader,
				 vmw_shader_key(user_key, shader_type),
				 res, list);
	vmw_resource_unreference(&res);
no_reserve:
	vmw_dmabuf_unreference(&buf);
out:
	return ret;
}
