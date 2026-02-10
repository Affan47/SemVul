process_game_info_packet( ubyte *data, header *hinfo )
{
	int offset;
	fix mission_time;
	ubyte paused;

	offset = HEADER_LENGTH;


	GET_INT( mission_time );
	GET_DATA( paused );
	PACKET_SET_SIZE();
}
