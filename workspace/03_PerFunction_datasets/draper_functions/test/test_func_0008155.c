fscache_alloc_object(struct fscache_cache *cache,
				struct fscache_cookie *cookie)
{
	struct fscache_object *object;
	int ret;

	_enter("%p,%p{%s}", cache, cookie, cookie->def->name);

	spin_lock(&cookie->lock);
	hlist_for_each_entry(object, &cookie->backing_objects,
			     cookie_link) {
		if (object->cache == cache)
			goto object_already_extant;
	}
	spin_unlock(&cookie->lock);


	fscache_stat(&fscache_n_cop_alloc_object);
	object = cache->ops->alloc_object(cache, cookie);
	fscache_stat_d(&fscache_n_cop_alloc_object);
	if (IS_ERR(object)) {
		fscache_stat(&fscache_n_object_no_alloc);
		ret = PTR_ERR(object);
		goto error;
	}

	fscache_stat(&fscache_n_object_alloc);

	object->debug_id = atomic_inc_return(&fscache_object_debug_id);

	_debug("ALLOC OBJ%x: %s {%lx}",
	       object->debug_id, cookie->def->name, object->events);

	ret = fscache_alloc_object(cache, cookie->parent);
	if (ret < 0)
		goto error_put;


	if (fscache_attach_object(cookie, object) < 0) {
		fscache_stat(&fscache_n_cop_put_object);
		cache->ops->put_object(object);
		fscache_stat_d(&fscache_n_cop_put_object);
	}

	_leave(" = 0");
	return 0;

object_already_extant:
	ret = -ENOBUFS;
	if (fscache_object_is_dying(object) ||
	    fscache_cache_is_broken(object)) {
		spin_unlock(&cookie->lock);
		goto error;
	}
	spin_unlock(&cookie->lock);
	_leave(" = 0 [found]");
	return 0;

error_put:
	fscache_stat(&fscache_n_cop_put_object);
	cache->ops->put_object(object);
	fscache_stat_d(&fscache_n_cop_put_object);
error:
	_leave(" = %d", ret);
	return ret;
}
