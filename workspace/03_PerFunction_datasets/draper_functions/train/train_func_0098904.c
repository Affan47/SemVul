load_mem_( byte const* in, long size )
{
	assert( offsetof (header_t,packed [4]) == header_size );
	int offset = 0;
	RETURN_ERR( check_header( in, size, &offset ) );
	set_voice_count( 8 );

	data     = in + offset;
	data_end = in + size;
	loop_begin = 0;

	if ( offset )
		header_ = *(header_t const*) in;
	else
		memset( &header_, 0, sizeof header_ );

	return 0;
}
