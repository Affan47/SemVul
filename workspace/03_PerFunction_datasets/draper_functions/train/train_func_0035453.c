FS2NetD_SendServerStart()
{
	int buffer_size;
	char buffer[550];
	ubyte tvar;

	INIT_PACKET( PCKT_SERVER_START );

	PXO_ADD_STRING( Netgame.name );
	PXO_ADD_STRING( Netgame.mission_name );
	PXO_ADD_STRING( Netgame.title );
	PXO_ADD_STRING( Netgame.campaign_name );

	tvar = (ubyte)Netgame.campaign_mode;
	PXO_ADD_DATA( tvar );

	PXO_ADD_INT( Netgame.flags );
	PXO_ADD_INT( Netgame.type_flags );

	PXO_ADD_SHORT( (short)multi_num_players() );
	PXO_ADD_SHORT( (short)Netgame.max_players );

	tvar = (ubyte)Netgame.mode;
	PXO_ADD_DATA( tvar );

	tvar = (ubyte)Netgame.rank_base;
	PXO_ADD_DATA( tvar );

	tvar = (ubyte)Netgame.game_state;
	PXO_ADD_DATA( tvar );

	tvar = (ubyte)multi_get_connection_speed();
	PXO_ADD_DATA( tvar );

	PXO_ADD_STRING(Multi_fs_tracker_channel);

	DONE_PACKET();

	FS2NetD_SendData(buffer, buffer_size);
}
