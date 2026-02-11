skype_check_keepalive(PurpleConnection *gc)
{
	if (last_pong < last_ping)
		purple_connection_error_reason(gc, PURPLE_CONNECTION_ERROR_NETWORK_ERROR, _("\nSkype not responding"));
	return FALSE;
}
