csnplNew ()
{
	CSNPL *csnpl;

	csnpl = (CSNPL *)slapi_ch_malloc (sizeof (CSNPL));
	if (csnpl == NULL)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"csnplNew: failed to allocate pending list\n");
		return NULL;
	}

	csnpl->csnList = llistNew ();
	if (csnpl->csnList == NULL)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"csnplNew: failed to allocate pending list\n");
		slapi_ch_free ((void**)&csnpl);
		return NULL;
	}


	csnpl->csnLock = slapi_new_rwlock();

	if (csnpl->csnLock == NULL)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"csnplNew: failed to create lock; NSPR error - %d\n",
						PR_GetError ());
		slapi_ch_free ((void**)&(csnpl->csnList));
		slapi_ch_free ((void**)&csnpl);
		return NULL;
	}

	return csnpl;
}
