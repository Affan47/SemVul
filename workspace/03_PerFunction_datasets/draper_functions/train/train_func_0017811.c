remap_track_( int* track_io ) const
{
	if ( (unsigned) *track_io >= (unsigned) track_count() )
		return "Invalid track";

	if ( (unsigned) *track_io < (unsigned) playlist.size() )
	{
		M3u_Playlist::entry_t const& e = playlist [*track_io];
		*track_io = 0;
		if ( e.track >= 0 )
		{
			*track_io = e.track;
			if ( !(type_->flags_ & 0x02) )
				*track_io -= e.decimal_track;
		}
		if ( *track_io >= raw_track_count_ )
			return "Invalid track in m3u playlist";
	}
	else
	{
		check( !playlist.size() );
	}
	return 0;
}
