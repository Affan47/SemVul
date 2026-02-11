send_mission_items( net_player *pl )
{
	ubyte data[MAX_PACKET_SIZE];
	int packet_size, i;
	ubyte stop, type;


	BUILD_HEADER(MISSION_ITEM);


	type = MISSION_LIST_ITEMS;
	ADD_DATA( type );
	for (i = 0; i < (int)Multi_create_mission_list.size(); i++ ) {
		stop = 0;
		ADD_DATA( stop );

		ADD_STRING( Multi_create_mission_list[i].filename );
		ADD_STRING( Multi_create_mission_list[i].name );
		ADD_INT( Multi_create_mission_list[i].flags );
		ADD_DATA( Multi_create_mission_list[i].max_players );
		ADD_INT( Multi_create_mission_list[i].respawn );


		ADD_DATA( Multi_create_mission_list[i].valid_status );

		if ( packet_size > (int)MAX_MISSION_ITEMS_BYTES ) {
			stop = 1;
			ADD_DATA( stop );
			multi_io_send_reliable(pl, data, packet_size);
			BUILD_HEADER( MISSION_ITEM );
			ADD_DATA( type );
		}
	}
	stop = 1;
	ADD_DATA(stop);
	multi_io_send_reliable(pl, data, packet_size);


	type = CAMPAIGN_LIST_ITEMS;
	BUILD_HEADER(MISSION_ITEM);
	ADD_DATA( type );
	for (i = 0; i < (int)Multi_create_campaign_list.size(); i++ ) {
		stop = 0;
		ADD_DATA( stop );

		ADD_STRING( Multi_create_campaign_list[i].filename );
		ADD_STRING( Multi_create_campaign_list[i].name );
		ADD_INT( Multi_create_campaign_list[i].flags );
		ADD_DATA( Multi_create_campaign_list[i].max_players );

		if ( packet_size > (int)MAX_MISSION_ITEMS_BYTES ) {
			stop = 1;
			ADD_DATA( stop );
			multi_io_send_reliable(pl, data, packet_size);
			BUILD_HEADER( MISSION_ITEM );
			ADD_DATA( type );
		}
	}
	stop = 1;
	ADD_DATA(stop);
	multi_io_send_reliable(pl, data, packet_size);
}
