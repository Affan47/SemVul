load_( Data_Reader& in )
{
	assert( offsetof (header_t,copyright [32]) == header_size );
	RETURN_ERR( rom.load( in, header_size, &header_, 0 ) );

	set_track_count( header_.track_count );
	RETURN_ERR( check_gbs_header( &header_ ) );

	if ( header_.vers != 1 )
		set_warning( "Unknown file version" );

	if ( header_.timer_mode & 0x78 )
		set_warning( "Invalid timer mode" );

	unsigned load_addr = GET_LE16( header_.load_addr );
	if ( (header_.load_addr [1] | header_.init_addr [1] | header_.play_addr [1]) > 0x7F ||
			load_addr < 0x400 )
		set_warning( "Invalid load/init/play address" );

	set_voice_count( Gb_Apu::osc_count );

	apu.volume( gain() );

	return setup_buffer( 4194304 );
}
