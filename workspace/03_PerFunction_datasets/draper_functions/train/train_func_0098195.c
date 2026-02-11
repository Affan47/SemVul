__fscache_uncache_page(struct fscache_cookie *cookie, struct page *page)
{
	struct fscache_object *object;

	_enter(",%p", page);

	ASSERTCMP(cookie->def->type, !=, FSCACHE_COOKIE_TYPE_INDEX);
	ASSERTCMP(page, !=, NULL);

	fscache_stat(&fscache_n_uncaches);


	if (!PageFsCache(page))
		goto done;


	spin_lock(&cookie->lock);

	if (hlist_empty(&cookie->backing_objects)) {
		ClearPageFsCache(page);
		goto done_unlock;
	}

	object = hlist_entry(cookie->backing_objects.first,
			     struct fscache_object, cookie_link);


	clear_bit(FSCACHE_COOKIE_NO_DATA_YET, &cookie->flags);


	if (TestClearPageFsCache(page) &&
	    object->cache->ops->uncache_page) {

		fscache_stat(&fscache_n_cop_uncache_page);
		object->cache->ops->uncache_page(object, page);
		fscache_stat_d(&fscache_n_cop_uncache_page);
		goto done;
	}

done_unlock:
	spin_unlock(&cookie->lock);
done:
	_leave("");
}
