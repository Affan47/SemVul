pnic_api_check ( uint16_t api_version ) {
	if ( api_version != PNIC_API_VERSION ) {
		printf ( "Warning: API version mismatch! "
			 "(NIC's is %d.%d, ours is %d.%d)\n",
			 api_version >> 8, api_version & 0xff,
			 PNIC_API_VERSION >> 8, PNIC_API_VERSION & 0xff );
	}
	if ( api_version < PNIC_API_VERSION ) {
		printf ( "** You may need to update your copy of Bochs **\n" );
	}
	return ( api_version == PNIC_API_VERSION );
}
