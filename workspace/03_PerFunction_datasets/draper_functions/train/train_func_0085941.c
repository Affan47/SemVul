unix_process(DWORD lparam)
{
	SDL_Event event;

	while( SDL_PollEvent(&event) ) {
		switch(event.type) {
			case SDL_ACTIVEEVENT:
				if( (event.active.state & SDL_APPACTIVE) || (event.active.state & SDL_APPINPUTFOCUS) ) {
					if (fAppActive != event.active.gain) {
						if (fAppActive)
							game_pause();
						else
							game_unpause();
					}
					fAppActive = event.active.gain;
					gr_activate(fAppActive);
				}
				break;

			case SDL_KEYDOWN:


				if( SDLtoFS2[event.key.keysym.sym] ) {
					key_mark( SDLtoFS2[event.key.keysym.sym], 1, 0 );
				}
				break;

			case SDL_KEYUP:


				if (SDLtoFS2[event.key.keysym.sym]) {
					key_mark( SDLtoFS2[event.key.keysym.sym], 0, 0 );
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					mouse_mark_button( MOUSE_LEFT_BUTTON, event.button.state );
				else if (event.button.button == SDL_BUTTON_MIDDLE)
					mouse_mark_button( MOUSE_MIDDLE_BUTTON, event.button.state );
				else if (event.button.button == SDL_BUTTON_RIGHT)
					mouse_mark_button( MOUSE_RIGHT_BUTTON, event.button.state );

				break;

			case SDL_JOYHATMOTION:
				joy_set_hat_state( event.jhat.value );
				break;

			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				if (event.jbutton.button < JOY_NUM_BUTTONS) {
					joy_set_button_state( event.jbutton.button, event.jbutton.state );
				}
				break;
		}
	}

	return 0;
}
