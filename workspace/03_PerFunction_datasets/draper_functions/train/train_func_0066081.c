ruvInit (RUV **ruv, int initCount)
{
	PR_ASSERT (ruv);

	if (ruv == NULL) {
		return RUV_NSPR_ERROR;
	}


	*ruv = (RUV *)slapi_ch_calloc (1, sizeof (RUV));


	(*ruv)->elements = dl_new ();

	dl_init ((*ruv)->elements, initCount);


	(*ruv)->lock = slapi_new_rwlock();
	if ((*ruv)->lock == NULL)
	{
		slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name,
						"ruvInit: failed to create lock\n");
		dl_free(&(*ruv)->elements);
		slapi_ch_free((void**)ruv);
		return RUV_NSPR_ERROR;
	}

	return RUV_SUCCESS;
}
