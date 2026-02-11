printn( const char *msg, va_list va )
{
	if (*msg == '\v')
		msg++;
	else
		flushn();
	vprintf( msg, va );
	fflush( stdout );
}
