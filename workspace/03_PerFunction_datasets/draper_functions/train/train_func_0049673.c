__vmw_execbuf_release_pinned_bo(struct vmw_private *dev_priv,
				     struct vmw_fence_obj *fence)
{
	int ret = 0;
	struct list_head validate_list;
	struct ttm_validate_buffer pinned_val, query_val;
	struct vmw_fence_obj *lfence = NULL;
	struct ww_acquire_ctx ticket;

	if (dev_priv->pinned_bo == NULL)
		goto out_unlock;

	INIT_LIST_HEAD(&validate_list);

	pinned_val.bo = ttm_bo_reference(&dev_priv->pinned_bo->base);
	pinned_val.shared = false;
	list_add_tail(&pinned_val.head, &validate_list);

	query_val.bo = ttm_bo_reference(&dev_priv->dummy_query_bo->base);
	query_val.shared = false;
	list_add_tail(&query_val.head, &validate_list);

	ret = ttm_eu_reserve_buffers(&ticket, &validate_list,
				     false, NULL);
	if (unlikely(ret != 0)) {
		vmw_execbuf_unpin_panic(dev_priv);
		goto out_no_reserve;
	}

	if (dev_priv->query_cid_valid) {
		BUG_ON(fence != NULL);
		ret = vmw_fifo_emit_dummy_query(dev_priv, dev_priv->query_cid);
		if (unlikely(ret != 0)) {
			vmw_execbuf_unpin_panic(dev_priv);
			goto out_no_emit;
		}
		dev_priv->query_cid_valid = false;
	}

	vmw_bo_pin_reserved(dev_priv->pinned_bo, false);
	if (dev_priv->dummy_query_bo_pinned) {
		vmw_bo_pin_reserved(dev_priv->dummy_query_bo, false);
		dev_priv->dummy_query_bo_pinned = false;
	}
	if (fence == NULL) {
		(void) vmw_execbuf_fence_commands(NULL, dev_priv, &lfence,
						  NULL);
		fence = lfence;
	}
	ttm_eu_fence_buffer_objects(&ticket, &validate_list, (void *) fence);
	if (lfence != NULL)
		vmw_fence_obj_unreference(&lfence);

	ttm_bo_unref(&query_val.bo);
	ttm_bo_unref(&pinned_val.bo);
	vmw_dmabuf_unreference(&dev_priv->pinned_bo);
	DRM_INFO("Dummy query bo pin count: %d\n",
		 dev_priv->dummy_query_bo->pin_count);

out_unlock:
	return;

out_no_emit:
	ttm_eu_backoff_reservation(&ticket, &validate_list);
out_no_reserve:
	ttm_bo_unref(&query_val.bo);
	ttm_bo_unref(&pinned_val.bo);
	vmw_dmabuf_unreference(&dev_priv->pinned_bo);
}
