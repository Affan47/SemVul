git_attr_cache__init(git_repository *repo)
{
	int ret;
	git_attr_cache *cache = git_repository_attr_cache(repo);
	git_config *cfg;

	if (cache->initialized)
		return 0;


	if (git_repository_config__weakptr(&cfg, repo) < 0)
		return -1;

	ret = git_config_get_string(&cache->cfg_attr_file, cfg, GIT_ATTR_CONFIG);
	if (ret < 0 && ret != GIT_ENOTFOUND)
		return ret;
	if (ret == GIT_ENOTFOUND)
		cache->cfg_attr_file = try_global_default(GIT_ATTR_CONFIG_DEFAULT);

	ret = git_config_get_string(&cache->cfg_excl_file, cfg, GIT_IGNORE_CONFIG);
	if (ret < 0 && ret != GIT_ENOTFOUND)
		return ret;
	if (ret == GIT_ENOTFOUND)
		cache->cfg_excl_file = try_global_default(GIT_IGNORE_CONFIG_DEFAULT);

	giterr_clear();


	if (cache->files == NULL) {
		cache->files = git_strmap_alloc();
		GITERR_CHECK_ALLOC(cache->files);
	}


	if (cache->macros == NULL) {
		cache->macros = git_strmap_alloc();
		GITERR_CHECK_ALLOC(cache->macros);
	}


	if (git_pool_init(&cache->pool, 1, 0) < 0)
		return -1;

	cache->initialized = 1;


	return git_attr_add_macro(repo, "binary", "-diff -crlf -text");
}
