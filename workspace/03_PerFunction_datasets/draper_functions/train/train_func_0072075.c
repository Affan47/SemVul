play_tracks(int track, int end_track)
{
	if (impl) return impl->play_tracks(track, end_track);
	return false;
}
