merge_server_config(apr_pool_t *p, void *basev, void *overridesv)
{
	scgi_server_cfg *c = (scgi_server_cfg *)
		apr_pcalloc(p, sizeof(scgi_server_cfg));
	scgi_server_cfg *base = (scgi_server_cfg *) basev;
	scgi_server_cfg *overrides = (scgi_server_cfg *) overridesv;

	c->mounts = apr_array_append(p, overrides->mounts, base->mounts);
        c->timeout = MERGE(base, overrides, timeout);
	return c;
}
