cachefiles_daemon_tag(struct cachefiles_cache *cache, char *args)
{
	char *tag;

	_enter(",%s", args);

	if (!*args) {
		pr_err("Empty tag specified\n");
		return -EINVAL;
	}

	if (cache->tag)
		return -EEXIST;

	tag = kstrdup(args, GFP_KERNEL);
	if (!tag)
		return -ENOMEM;

	cache->tag = tag;
	return 0;
}
