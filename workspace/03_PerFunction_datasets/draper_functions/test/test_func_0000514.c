copy_ay_fields( Ay_Emu::file_t const& file, track_info_t* out, int track )
{
	Gme_File::copy_field_( out->song, (char const*) get_data( file, file.tracks + track * 4, 1 ) );
	byte const* track_info = get_data( file, file.tracks + track * 4 + 2, 6 );
	if ( track_info )
		out->length = GET_BE16( track_info + 4 ) * (1000L / 50);

	Gme_File::copy_field_( out->author,  (char const*) get_data( file, file.header->author, 1 ) );
	Gme_File::copy_field_( out->comment, (char const*) get_data( file, file.header->comment, 1 ) );
}
