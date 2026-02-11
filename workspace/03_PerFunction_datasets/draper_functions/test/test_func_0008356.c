FCEUI_MoviePlayFromBeginning(void)
{
	if (movieMode == MOVIEMODE_TASEDITOR)
	{
#ifdef WIN32
		handleEmuCmdByTaseditor(EMUCMD_MOVIE_PLAY_FROM_BEGINNING);
#endif
	} else if (movieMode != MOVIEMODE_INACTIVE)
	{
		if (currMovieData.savestate.empty())
		{
			movie_readonly=true;
			movieMode = MOVIEMODE_PLAY;
			poweron(true);
			currFrameCounter=0;
			FCEU_DispMessage("Movie is now Read-Only. Playing from beginning.",0);
		}
		else
		{

			string str = curMovieFilename;
			FCEUI_StopMovie();
			if (FCEUI_LoadMovie(str.c_str(), 1, 0))
			{
				movieMode = MOVIEMODE_PLAY;
				movie_readonly = true;
				FCEU_DispMessage("Movie is now Read-Only. Playing from beginning.",0);
			}

		}
	}
#ifdef WIN32
	SetMainWindowText();
#endif
}
