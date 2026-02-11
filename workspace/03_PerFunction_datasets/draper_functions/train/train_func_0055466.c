PLATFORM_Initialise(int *argc, char *argv[])
{
	int i, j;
	int help_only = FALSE;

	for (i = j = 1; i < *argc; i++) {
		if (strcmp(argv[i], "-help") == 0) {
			help_only = TRUE;
		}
		argv[j++] = argv[i];
	}
	*argc = j;

	if (!help_only) {
		i = SDL_INIT_JOYSTICK
#if HAVE_WINDOWS_H

		    | SDL_INIT_TIMER
#endif
		;
		if (SDL_InitSubSystem(i) != 0) {
			Log_print("SDL_InitSubSystem FAILED: %s", SDL_GetError());
			Log_flushlog();
			exit(-1);
		}
	}

	if (!SDL_VIDEO_Initialise(argc, argv)
#ifdef SOUND
	    || !Sound_Initialise(argc, argv)
#endif
	    || !SDL_INPUT_Initialise(argc, argv))
		return FALSE;

	return TRUE;
}
