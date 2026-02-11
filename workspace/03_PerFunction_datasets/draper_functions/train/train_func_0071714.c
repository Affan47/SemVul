track_info_( track_info_t* out, int track ) const
{
	int remapped = remap_track( track );
	if ( (unsigned) remapped < track_times.size() )
	{
		long length = (int32_t) GET_LE32( track_times [remapped] );
		if ( length > 0 )
			out->length = length;
	}
	if ( (unsigned) remapped < track_names.size() )
		Gme_File::copy_field_( out->song, track_names [remapped] );

	GME_COPY_FIELD( info, out, game );
	GME_COPY_FIELD( info, out, author );
	GME_COPY_FIELD( info, out, copyright );
	GME_COPY_FIELD( info, out, dumper );
	return 0;
}
