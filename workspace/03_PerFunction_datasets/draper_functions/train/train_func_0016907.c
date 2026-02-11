IRCH_PrivMsg( )
{
	qboolean is_channel;

	if ( IRC_ReceivedMessage.arg_count != 2 ) {
		return IRC_CMD_SUCCESS;
	}


	is_channel = IRC_String( arg_values[ 0 ] )[ 0 ] == '#';
	if ( is_channel && strcmp( &( IRC_String( arg_values[ 0 ] )[ 1 ] ) , cl_IRC_channel->string ) )
		return IRC_CMD_SUCCESS;

	if ( IRC_Length( arg_values[ 1 ] ) > 2
			&& IRC_String( arg_values[ 1 ] )[ 0 ] == 1
			&& IRC_String( arg_values[ 1 ] )[ IRC_Length( arg_values[ 1 ] ) - 1 ] == 1 ) {
		return IRC_HandleCTCP( is_channel , IRC_String( arg_values[ 1 ] ) + 1 , IRC_Length( arg_values[ 1 ] ) - 1 );
	}

	return IRC_HandleMessage( is_channel , IRC_String( arg_values[ 1 ] ) );
}
