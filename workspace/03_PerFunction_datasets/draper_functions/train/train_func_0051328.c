mnt_context_set_cache(struct libmnt_context *cxt, struct libmnt_cache *cache)
{
	if (!cxt)
		return -EINVAL;
	if (!(cxt->flags & MNT_FL_EXTERN_CACHE))
		mnt_free_cache(cxt->cache);

	set_flag(cxt, MNT_FL_EXTERN_CACHE, cache != NULL);
	cxt->cache = cache;
	return 0;
}
