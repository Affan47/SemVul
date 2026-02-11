activation(SDL_Event *event)
{
	Global *game = Global::getInstance();
	Config* config = Config::instance();
	if( config->debug() ) fprintf(stderr, "app %s ", event->active.gain ? "gained" : "lost" );
	bool grab_mouse = game->gameMode == Global::Game && !game->game_pause && event->active.gain ? true : false;
	if ( event->active.state & SDL_APPACTIVE )
	{
		grabMouse( grab_mouse, grab_mouse );
		if( config->debug() ) fprintf(stderr, "app active " );
	}
	else if ( event->active.state & SDL_APPMOUSEFOCUS )
	{
		if( config->debug() ) fprintf(stderr, _("mouse active") );
		SDL_GetMouseState(&xLast, &yLast);
	}
	else if ( event->active.state & SDL_APPINPUTFOCUS )
	{
		grabMouse( grab_mouse, grab_mouse );
		if( config->debug() ) fprintf(stderr, "input active" );
	}
	if( config->debug() ) fprintf(stderr, _("focus\n") );
}
