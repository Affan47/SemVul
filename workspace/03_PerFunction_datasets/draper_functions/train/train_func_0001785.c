pg_timezone_initialize(void)
{
	pg_tz	   *def_tz = NULL;


	if (!session_timezone)
	{
		def_tz = select_default_timezone();
		session_timezone = def_tz;
	}
	if (!log_timezone)
	{

		if (!def_tz)
			def_tz = select_default_timezone();
		log_timezone = def_tz;
	}


	if (GetConfigOptionResetString("timezone") == NULL)
		SetConfigOption("timezone", pg_get_timezone_name(session_timezone),
						PGC_POSTMASTER, PGC_S_ENV_VAR);

	if (GetConfigOptionResetString("log_timezone") == NULL)
		SetConfigOption("log_timezone", pg_get_timezone_name(log_timezone),
						PGC_POSTMASTER, PGC_S_ENV_VAR);
}
