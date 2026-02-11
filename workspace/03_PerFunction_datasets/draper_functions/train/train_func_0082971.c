disable_playlist( bool b )
{
	playlist_disabled = b;
	info.track_count = playlist.size();
	if ( !info.track_count || playlist_disabled )
		info.track_count = actual_track_count_;
}
