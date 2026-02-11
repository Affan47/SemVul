CTCP_Ping( qboolean is_channel , const char * argument )
{
	if ( is_channel || !IRC_CheckEventRate( IRC_RL_PING ) )
		return IRC_CMD_SUCCESS;

	if ( *argument )
		return IRC_Send( "NOTICE %s :\001PING %s\001" , IRC_String( pfx_nickOrServer ) , argument );

	return IRC_Send( "NOTICE %s :\001PING\001" , IRC_String( pfx_nickOrServer ) );
}
