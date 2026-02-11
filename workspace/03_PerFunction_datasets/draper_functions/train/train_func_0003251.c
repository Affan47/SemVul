do_cache_lookup_nowait(struct cache_detail *cd,
		struct nfs_dns_ent *key,
		struct nfs_dns_ent **item)
{
	int ret = -ENOMEM;

	*item = nfs_dns_lookup(cd, key);
	if (!*item)
		goto out_err;
	ret = -ETIMEDOUT;
	if (!test_bit(CACHE_VALID, &(*item)->h.flags)
			|| (*item)->h.expiry_time < seconds_since_boot()
			|| cd->flush_time > (*item)->h.last_refresh)
		goto out_put;
	ret = -ENOENT;
	if (test_bit(CACHE_NEGATIVE, &(*item)->h.flags))
		goto out_put;
	return 0;
out_put:
	cache_put(&(*item)->h, cd);
out_err:
	*item = NULL;
	return ret;
}
