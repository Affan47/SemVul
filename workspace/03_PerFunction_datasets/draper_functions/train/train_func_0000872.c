__fscache_relinquish_cookie(struct fscache_cookie *cookie, bool retire)
{
	fscache_stat(&fscache_n_relinquishes);
	if (retire)
		fscache_stat(&fscache_n_relinquishes_retire);

	if (!cookie) {
		fscache_stat(&fscache_n_relinquishes_null);
		_leave(" [no cookie]");
		return;
	}

	_enter("%p{%s,%p,%d},%d",
	       cookie, cookie->def->name, cookie->netfs_data,
	       atomic_read(&cookie->n_active), retire);


	set_bit(FSCACHE_COOKIE_RELINQUISHED, &cookie->flags);

	__fscache_disable_cookie(cookie, retire);


	cookie->netfs_data	= NULL;
	cookie->def		= NULL;
	BUG_ON(cookie->stores.rnode);

	if (cookie->parent) {
		ASSERTCMP(atomic_read(&cookie->parent->usage), >, 0);
		ASSERTCMP(atomic_read(&cookie->parent->n_children), >, 0);
		atomic_dec(&cookie->parent->n_children);
	}


	ASSERTCMP(atomic_read(&cookie->usage), >, 0);
	fscache_cookie_put(cookie);

	_leave("");
}
