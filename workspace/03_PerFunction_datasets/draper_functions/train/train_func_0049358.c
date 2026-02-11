vmw_cmdbuf_res_remove(struct vmw_cmdbuf_res_manager *man,
			  enum vmw_cmdbuf_res_type res_type,
			  u32 user_key,
			  struct list_head *list,
			  struct vmw_resource **res_p)
{
	struct vmw_cmdbuf_res *entry;
	struct drm_hash_item *hash;
	int ret;

	ret = drm_ht_find_item(&man->resources, user_key | (res_type << 24),
			       &hash);
	if (likely(ret != 0))
		return -EINVAL;

	entry = drm_hash_entry(hash, struct vmw_cmdbuf_res, hash);

	switch (entry->state) {
	case VMW_CMDBUF_RES_ADD:
		vmw_cmdbuf_res_free(man, entry);
		*res_p = NULL;
		break;
	case VMW_CMDBUF_RES_COMMITTED:
		(void) drm_ht_remove_item(&man->resources, &entry->hash);
		list_del(&entry->head);
		entry->state = VMW_CMDBUF_RES_DEL;
		list_add_tail(&entry->head, list);
		*res_p = entry->res;
		break;
	default:
		BUG();
		break;
	}

	return 0;
}
