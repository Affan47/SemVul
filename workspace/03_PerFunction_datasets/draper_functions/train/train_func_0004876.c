_stream_error_function(
    const DB_ENV *dbenv, const char *prefix, const char *message)
{
	const DbEnv *cxxenv = DbEnv::get_const_DbEnv(dbenv);
	if (cxxenv == 0) {
		DB_ERROR(0,
		    "DbEnv::stream_error", EINVAL, ON_ERROR_UNKNOWN);
		return;
	}

	if (cxxenv->error_callback_)
		cxxenv->error_callback_(cxxenv, prefix, message);
	else if (cxxenv->error_stream_) {

		if (prefix) {
			(*cxxenv->error_stream_) << prefix;
			(*cxxenv->error_stream_) << (const char *)": ";
		}
		if (message)
			(*cxxenv->error_stream_) << (const char *)message;
		(*cxxenv->error_stream_) << (const char *)"\n";
	}
}
