joystick_init (void) {
	SDL_JoystickEventState (SDL_ENABLE);
	if (SDL_NumJoysticks () >= JOY_INDEX) {
		joy = SDL_JoystickOpen (JOY_INDEX);

		if (joy == NULL) {
#ifdef DEBUG
			printf ("Failed to open joystick.\n");
#endif
			return (1);
		}
		else
			return (0);
	}
	else {
#ifdef DEBUG
		printf ("Joystick not found.\n");
#endif
		return (2);
	}
}
