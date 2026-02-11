cachefiles_check_consistency(struct fscache_operation *op)
{
	struct cachefiles_object *object;
	struct cachefiles_cache *cache;
	const struct cred *saved_cred;
	int ret;

	_enter("{OBJ%x}", op->object->debug_id);

	object = container_of(op->object, struct cachefiles_object, fscache);
	cache = container_of(object->fscache.cache,
			     struct cachefiles_cache, cache);

	cachefiles_begin_secure(cache, &saved_cred);
	ret = cachefiles_check_auxdata(object);
	cachefiles_end_secure(cache, saved_cred);

	_leave(" = %d", ret);
	return ret;
}
