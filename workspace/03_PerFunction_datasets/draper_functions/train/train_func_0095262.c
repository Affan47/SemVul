hset_foreach(const hset_t *hx, cdata_fn_t fn, void *data)
{
	unsigned *hp, *end;
	size_t i, n;

	hset_check(hx);

	end = &hx->kset.hashes[hx->kset.size];
	hash_refcnt_inc(HASH(hx));

	for (i = n = 0, hp = hx->kset.hashes; hp != end; i++, hp++) {
		if (HASH_IS_REAL(*hp)) {
			(*fn)(hx->kset.keys[i], data);
			n++;
		}
	}

	g_assert(n == hx->kset.items);

	hash_refcnt_dec(HASH(hx));
}
