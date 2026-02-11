cachefiles_invalidate_object(struct fscache_operation *op)
{
	struct cachefiles_object *object;
	struct cachefiles_cache *cache;
	const struct cred *saved_cred;
	struct path path;
	uint64_t ni_size;
	int ret;

	object = container_of(op->object, struct cachefiles_object, fscache);
	cache = container_of(object->fscache.cache,
			     struct cachefiles_cache, cache);

	op->object->cookie->def->get_attr(op->object->cookie->netfs_data,
					  &ni_size);

	_enter("{OBJ%x},[%llu]",
	       op->object->debug_id, (unsigned long long)ni_size);

	if (object->backer) {
		ASSERT(d_is_reg(object->backer));

		fscache_set_store_limit(&object->fscache, ni_size);

		path.dentry = object->backer;
		path.mnt = cache->mnt;

		cachefiles_begin_secure(cache, &saved_cred);
		ret = vfs_truncate(&path, 0);
		if (ret == 0)
			ret = vfs_truncate(&path, ni_size);
		cachefiles_end_secure(cache, saved_cred);

		if (ret != 0) {
			fscache_set_store_limit(&object->fscache, 0);
			if (ret == -EIO)
				cachefiles_io_error_obj(object,
							"Invalidate failed");
		}
	}

	fscache_op_complete(op, true);
	_leave("");
}
