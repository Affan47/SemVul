gd3_data( int* size ) const
{
	if ( size )
		*size = 0;

	long gd3_offset = GET_LE32( header().gd3_offset ) - 0x2C;
	if ( gd3_offset < 0 )
		return 0;

	byte const* gd3 = data + header_size + gd3_offset;
	long gd3_size = check_gd3_header( gd3, data_end - gd3 );
	if ( !gd3_size )
		return 0;

	if ( size )
		*size = gd3_size + gd3_header_size;

	return gd3;
}
