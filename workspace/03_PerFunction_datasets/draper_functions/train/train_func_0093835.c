setMusicIndex(int index)
{
#ifdef USE_SDL
	Config	*config = Config::instance();
	if(config->audioEnabled() == true)
	{
		bool	wasPlaying = false;
		if(musicMax)
			musicIndex = index%musicMax;
		if( config->debug() ) fprintf(stderr, _("Audio::setMusicIndex(%d)\n"), musicIndex);

		if(cdrom)
		{
			int cdromStatus = SDL_CDStatus(cdrom);
			if(cdromStatus == CD_PLAYING)
				wasPlaying = true;

			if(cdrom->track[musicIndex].type < SDL_DATA_TRACK)
			{
				SDL_CDStop(cdrom);
				SDL_CDPlayTracks(cdrom, musicIndex, 0, 1, 0);
				if(!wasPlaying)
					SDL_CDPause(cdrom);
			}
			else
			{
				if( config->debug() ) fprintf(stderr, _("track %d is data - trying next track...\n"), musicIndex);
				Audio::setMusicIndex(musicIndex+1);
			}
		}
	}
#endif
}
