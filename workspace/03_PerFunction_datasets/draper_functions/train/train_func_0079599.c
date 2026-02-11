cachefiles_put_object(struct fscache_object *_object)
{
	struct cachefiles_object *object;
	struct fscache_cache *cache;

	ASSERT(_object);

	object = container_of(_object, struct cachefiles_object, fscache);

	_enter("{OBJ%x,%d}",
	       object->fscache.debug_id, atomic_read(&object->usage));

#ifdef CACHEFILES_DEBUG_SLAB
	ASSERT((atomic_read(&object->usage) & 0xffff0000) != 0x6b6b0000);
#endif

	ASSERTIFCMP(object->fscache.parent,
		    object->fscache.parent->n_children, >, 0);

	if (atomic_dec_and_test(&object->usage)) {
		_debug("- kill object OBJ%x", object->fscache.debug_id);

		ASSERT(!test_bit(CACHEFILES_OBJECT_ACTIVE, &object->flags));
		ASSERTCMP(object->fscache.parent, ==, NULL);
		ASSERTCMP(object->backer, ==, NULL);
		ASSERTCMP(object->dentry, ==, NULL);
		ASSERTCMP(object->fscache.n_ops, ==, 0);
		ASSERTCMP(object->fscache.n_children, ==, 0);

		if (object->lookup_data) {
			kfree(object->lookup_data->key);
			kfree(object->lookup_data->auxdata);
			kfree(object->lookup_data);
			object->lookup_data = NULL;
		}

		cache = object->fscache.cache;
		fscache_object_destroy(&object->fscache);
		kmem_cache_free(cachefiles_object_jar, object);
		fscache_object_destroyed(cache);
	}

	_leave("");
}
