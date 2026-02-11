csnplRemove (CSNPL *csnpl, const CSN *csn)
{
	csnpldata *data;
	char csn_str[CSN_STRSIZE];

    if (csnpl == NULL || csn == NULL)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
			"csnplRemove: invalid argument\n");
		return -1;
	}

	csn_as_string(csn, PR_FALSE, csn_str);
	slapi_rwlock_wrlock (csnpl->csnLock);

	data = (csnpldata *)llistRemove (csnpl->csnList, csn_str);
	if (data == NULL)
	{
		slapi_rwlock_unlock (csnpl->csnLock);
		return -1;
	}

#ifdef DEBUG
    _csnplDumpContentNoLock(csnpl, "csnplRemove");
#endif

	csn_free(&data->csn);
	slapi_ch_free((void **)&data);

	slapi_rwlock_unlock (csnpl->csnLock);

	return 0;
}
