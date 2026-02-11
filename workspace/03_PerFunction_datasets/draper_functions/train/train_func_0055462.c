enter()
{
	audio_channel_stop(0, -1);
	run_intro = 0;
	manage.game_start();
	if(exit_game || manage.game_stopped())
	{
		st_error.message("Could not start game!",
				"Please, check your installation.");
		gsm.change(&st_error);
	}
	if(prefs->mousecapture)
		if(SDL_WM_GrabInput(SDL_GRAB_QUERY) != SDL_GRAB_ON)
			SDL_WM_GrabInput(SDL_GRAB_ON);
}
