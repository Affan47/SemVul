fscache_attach_object(struct fscache_cookie *cookie,
				 struct fscache_object *object)
{
	struct fscache_object *p;
	struct fscache_cache *cache = object->cache;
	int ret;

	_enter("{%s},{OBJ%x}", cookie->def->name, object->debug_id);

	spin_lock(&cookie->lock);


	ret = -EEXIST;
	hlist_for_each_entry(p, &cookie->backing_objects, cookie_link) {
		if (p->cache == object->cache) {
			if (fscache_object_is_dying(p))
				ret = -ENOBUFS;
			goto cant_attach_object;
		}
	}


	spin_lock_nested(&cookie->parent->lock, 1);
	hlist_for_each_entry(p, &cookie->parent->backing_objects,
			     cookie_link) {
		if (p->cache == object->cache) {
			if (fscache_object_is_dying(p)) {
				ret = -ENOBUFS;
				spin_unlock(&cookie->parent->lock);
				goto cant_attach_object;
			}
			object->parent = p;
			spin_lock(&p->lock);
			p->n_children++;
			spin_unlock(&p->lock);
			break;
		}
	}
	spin_unlock(&cookie->parent->lock);


	if (list_empty(&object->cache_link)) {
		spin_lock(&cache->object_list_lock);
		list_add(&object->cache_link, &cache->object_list);
		spin_unlock(&cache->object_list_lock);
	}


	object->cookie = cookie;
	atomic_inc(&cookie->usage);
	hlist_add_head(&object->cookie_link, &cookie->backing_objects);

	fscache_objlist_add(object);
	ret = 0;

cant_attach_object:
	spin_unlock(&cookie->lock);
	_leave(" = %d", ret);
	return ret;
}
