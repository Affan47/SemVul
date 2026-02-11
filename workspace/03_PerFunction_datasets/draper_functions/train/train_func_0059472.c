sys_error( const char *msg, ... )
{
	va_list va;
	char buf[1024];

	flushn();
	va_start( va, msg );
	if ((unsigned)vsnprintf( buf, sizeof(buf), msg, va ) >= sizeof(buf))
		oob();
	va_end( va );
	perror( buf );
}
