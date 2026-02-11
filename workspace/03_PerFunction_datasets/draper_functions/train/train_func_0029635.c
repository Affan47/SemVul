send_hud_msg_to_all( char* msg )
{
	ubyte data[MAX_PACKET_SIZE];
	int packet_size;


	BUILD_HEADER(HUD_MSG);

	ADD_STRING(msg);

	multi_io_send_to_all( data, packet_size );
}
