pw_entry_constructor(void *object, void *parent)
{
	struct slapi_pw_entry_ext *pw_extp = NULL;
	Slapi_RWLock *rwlock;
	if ((rwlock = slapi_new_rwlock()) == NULL) {
		slapi_log_error(SLAPI_LOG_FATAL, NULL,
		                "pw_entry_constructor: slapi_new_rwlock() failed\n");
		slapi_log_error(SLAPI_LOG_FATAL, NULL,
		                "WARNING: the server cannot handle unhashed password.\n");
		return NULL;
	}
	pw_extp = (struct slapi_pw_entry_ext *)slapi_ch_calloc(1,
                                             sizeof(struct slapi_pw_entry_ext));
	pw_extp->pw_entry_lock = rwlock;
	return pw_extp;
}
