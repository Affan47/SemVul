courier_authdebug_login_init( void )
{
	const char *p=getenv(DEBUG_LOGIN_ENV);

	courier_authdebug_login_level = atoi( p ? p:"0" );
}
