php_sqlite_authorizer(void *autharg, int access_type, const char *arg3, const char *arg4,
		const char *arg5, const char *arg6)
{
	switch (access_type) {
		case SQLITE_COPY:
			if (strncmp(arg4, ":memory:", sizeof(":memory:") - 1)) {
				TSRMLS_FETCH();
				if (PG(safe_mode) && (!php_checkuid(arg4, NULL, CHECKUID_CHECK_FILE_AND_DIR))) {
					return SQLITE_DENY;
				}

				if (php_check_open_basedir(arg4 TSRMLS_CC)) {
					return SQLITE_DENY;
				}
			}
			return SQLITE_OK;
#ifdef SQLITE_ATTACH
		case SQLITE_ATTACH:
			if (strncmp(arg3, ":memory:", sizeof(":memory:") - 1)) {
				TSRMLS_FETCH();
				if (PG(safe_mode) && (!php_checkuid(arg3, NULL, CHECKUID_CHECK_FILE_AND_DIR))) {
					return SQLITE_DENY;
				}

				if (php_check_open_basedir(arg3 TSRMLS_CC)) {
					return SQLITE_DENY;
				}
			}
			return SQLITE_OK;
#endif

		default:

			return SQLITE_OK;
	}
}
