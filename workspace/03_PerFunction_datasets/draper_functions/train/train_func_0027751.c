__db_err(const ENV *env, int error, const char *fmt, ...)
#else
__db_err(env, error, fmt, va_alist)
	const ENV *env;
	int error;
	const char *fmt;
	va_dcl
#endif
{
	DB_ENV *dbenv;

	dbenv = env == NULL ? NULL : env->dbenv;


	DB_REAL_ERR(dbenv, error, DB_ERROR_SET, 0, fmt);
}
