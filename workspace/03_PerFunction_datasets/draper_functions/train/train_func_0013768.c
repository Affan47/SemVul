info_looper(Playlist *playlist)
{
	CorePlayer *myplayer;
	stream_info info;
	int t_sec, count;

	std::set<PlaylistInterface *>::const_iterator i;
	std::set<playlist_interface *>::const_iterator j;

	if (!playlist) return;

	myplayer = new CorePlayer(NULL);

	if (!myplayer) return;

	std::vector<PlayItem>::iterator p = playlist->queue.begin();
	count = 0;
	while (playlist->active) {

		const char *path;

		if (p >= playlist->queue.end()) {


		    break;
		}

		if (!(*p).Parsed()) {
			path = (*p).filename.c_str();

			if (path && !strstr(path, "http://") &&
					myplayer->Open((*p).filename.c_str())) {
				t_sec = myplayer->GetCurrentTime(myplayer->GetFrames());
				if (t_sec) {
					t_sec /= 100;
					(*p).playtime = t_sec;
				} else {
					(*p).playtime = -1;
				}
				if (myplayer->GetStreamInfo(&info)) {
					(*p).title = info.title;
					(*p).artist = info.artist;
					(*p).album = info.album;
					(*p).genre = info.genre;
					(*p).year = info.year;
					(*p).track = info.track;
					(*p).comment = info.comment;
				}
				myplayer->Close();
			}
			(*p).SetParsed();

			playlist->LockInterfaces();
			if (playlist->interfaces.size() > 0) {
				for(i = playlist->interfaces.begin();
						i != playlist->interfaces.end(); i++) {
					(*i)->CbUpdated((*p), count);
				}
			}
			if (playlist->cinterfaces.size() > 0) {
				for (j = playlist->cinterfaces.begin();
						j != playlist->cinterfaces.end(); j++) {
					(*j)->cbupdated((*j)->data, (*p), count);
				}
			}
			playlist->UnlockInterfaces();
		}
		p++;
		count++;

	}

	delete myplayer;

}
