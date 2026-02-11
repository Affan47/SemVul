perfctrs_terminate(perfctrs_private **priv, DB_ENV *db_env)
{
	DB_MPOOL_STAT *mpstat = NULL;
	DB_TXN_STAT   *txnstat = NULL;
	DB_LOG_STAT   *logstat = NULL;
	DB_LOCK_STAT  *lockstat = NULL;

	MEMP_STAT(db_env, &mpstat, NULL, DB_STAT_CLEAR, (void *)slapi_ch_malloc);
	slapi_ch_free((void**)&mpstat);
	TXN_STAT(db_env, &txnstat, DB_STAT_CLEAR, (void *)slapi_ch_malloc);
	slapi_ch_free((void**)&txnstat);
	LOG_STAT(db_env, &logstat, DB_STAT_CLEAR, (void *)slapi_ch_malloc);
	slapi_ch_free((void**)&logstat);
	LOCK_STAT(db_env, &lockstat, DB_STAT_CLEAR, (void *)slapi_ch_malloc);
	slapi_ch_free((void**)&lockstat);
#if defined(_WIN32)
	if (NULL != (*priv)->memory) {
		UnmapViewOfFile((*priv)->memory);
	}
	if (NULL != (*priv)->hMemory) {
		CloseHandle((*priv)->hMemory);
	}
	if (NULL != (*priv)->hEvent) {
		CloseHandle((*priv)->hEvent);
	}
#else
	if (NULL != (*priv)->memory) {
		slapi_ch_free(&(*priv)->memory);
	}
#endif

	slapi_ch_free( (void **)priv );
}
