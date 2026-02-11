store_users(apr_array_header_t *users,
		const char *file_name,
		apr_pool_t *pool)
{
	apr_pool_t *_pool;
	apr_status_t res;
	apr_file_t *f;
	dynalogin_user_data_t *u;
	int i;
	char *s;

	if((res = apr_pool_create(&_pool, pool)) != APR_SUCCESS)
		return res;

	if(res=apr_file_open(&f, file_name,
			APR_WRITE | APR_SHARELOCK | APR_TRUNCATE,
			0, _pool)
			!= APR_SUCCESS)
	{
		apr_pool_destroy(_pool);
		return res;
	}

	i = 0;
	for(u = (dynalogin_user_data_t *)(users->elts);
			i < users->nelts && u[i].userid != NULL;
			i++)
	{
		s = apr_psprintf(_pool, "%s:%s:%s:%d:%d:%d:%ld:%ld:%s\n",
				u[i].userid, get_scheme_name(u[i].scheme), u[i].secret,
				u[i].counter, u[i].failure_count, u[i].locked,
				u[i].last_success, u[i].last_attempt,
				u[i].last_code);
		syslog(LOG_DEBUG, "writing: %s", s);

		if((res=apr_file_puts(s, f))!=APR_SUCCESS)
		{
			apr_file_close(f);
			apr_pool_destroy(_pool);
			return res;
		}
	}

	apr_file_close(f);
	apr_pool_destroy(_pool);

	return APR_SUCCESS;
}
