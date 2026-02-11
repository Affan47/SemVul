calc_ttl()
{
	if (!ctx.repo)
		return ctx.cfg.cache_root_ttl;

	if (!ctx.qry.page)
		return ctx.cfg.cache_repo_ttl;

	if (ctx.qry.has_symref)
		return ctx.cfg.cache_dynamic_ttl;

	if (ctx.qry.has_sha1)
		return ctx.cfg.cache_static_ttl;

	return ctx.cfg.cache_repo_ttl;
}
