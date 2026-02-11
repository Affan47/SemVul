fscache_look_up_object(struct fscache_object *object,
							  int event)
{
	struct fscache_cookie *cookie = object->cookie;
	struct fscache_object *parent = object->parent;
	int ret;

	_enter("{OBJ%x},%d", object->debug_id, event);

	object->oob_table = fscache_osm_lookup_oob;

	ASSERT(parent != NULL);
	ASSERTCMP(parent->n_ops, >, 0);
	ASSERTCMP(parent->n_obj_ops, >, 0);


	ASSERT(fscache_object_is_available(parent));

	if (fscache_object_is_dying(parent) ||
	    test_bit(FSCACHE_IOERROR, &object->cache->flags) ||
	    !fscache_use_cookie(object)) {
		_leave(" [unavailable]");
		return transit_to(LOOKUP_FAILURE);
	}

	_debug("LOOKUP \"%s\" in \"%s\"",
	       cookie->def->name, object->cache->tag->name);

	fscache_stat(&fscache_n_object_lookups);
	fscache_stat(&fscache_n_cop_lookup_object);
	ret = object->cache->ops->lookup_object(object);
	fscache_stat_d(&fscache_n_cop_lookup_object);

	fscache_unuse_cookie(object);

	if (ret == -ETIMEDOUT) {


		fscache_stat(&fscache_n_object_lookups_timed_out);
		_leave(" [timeout]");
		return NO_TRANSIT;
	}

	if (ret < 0) {
		_leave(" [error]");
		return transit_to(LOOKUP_FAILURE);
	}

	_leave(" [ok]");
	return transit_to(OBJECT_AVAILABLE);
}
