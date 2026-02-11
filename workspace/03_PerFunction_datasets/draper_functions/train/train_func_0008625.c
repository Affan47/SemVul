optiquery( const char *cmd )
{
	upsdebugx(2, "SEND: \"%s\"", cmd );
	ser_send( upsfd, "%s", cmd );
	if ( optimodel == OPTIMODEL_ZINTO )
		ser_send( upsfd, "\r\n" );
	return optireadline();
}
