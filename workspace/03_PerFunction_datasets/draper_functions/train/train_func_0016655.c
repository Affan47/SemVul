loadSDL()
	{

#ifndef Q_OS_WIN
		QLibrary mixer_lib("SDL2_mixer");
		if (!mixer_lib.load()) {
			mixer_lib.setFileName("SDL_mixer");
		}
		if (!mixer_lib.load()) {
			mixer_lib.setFileNameAndVersion("SDL2_mixer-2.0", "0");
		}
		if (!mixer_lib.load()) {
			mixer_lib.setFileNameAndVersion("SDL_mixer-1.2", "0");
		}
#else
		QLibrary mixer_lib("SDL");
#endif
		sdl_Init = (func_SDL_Init) mixer_lib.resolve("SDL_Init");
		sdl_Quit = (func_SDL_Quit) mixer_lib.resolve("SDL_Quit");
		sdl_GetError = (func_SDL_GetError) mixer_lib.resolve("SDL_GetError");
		sdl_RWFromFile = (func_SDL_RWFromFile) mixer_lib.resolve("SDL_RWFromFile");
		if ((sdl_Init == 0) || (sdl_Quit == 0) || (sdl_GetError == 0) || (sdl_RWFromFile == 0)) {
			qWarning("Unable to load SDL");
			return;
		}
		if (sdl_Init(SDL_INIT_AUDIO) != 0) {
			qWarning("Unable to initialize SDL: %s", sdl_GetError());
			return;
		}


#ifdef Q_OS_WIN
		mixer_lib.setFileName("SDL_mixer");
#endif
		mix_OpenAudio = (func_Mix_OpenAudio) mixer_lib.resolve("Mix_OpenAudio");
		mix_CloseAudio = (func_Mix_CloseAudio) mixer_lib.resolve("Mix_CloseAudio");
		mix_LoadWAV_RW = (func_Mix_LoadWAV_RW) mixer_lib.resolve("Mix_LoadWAV_RW");
		mix_FreeChunk = (func_Mix_FreeChunk) mixer_lib.resolve("Mix_FreeChunk");
		mix_PlayChannelTimed = (func_Mix_PlayChannelTimed) mixer_lib.resolve("Mix_PlayChannelTimed");
		if ((mix_OpenAudio == 0) || (mix_CloseAudio == 0) || (mix_LoadWAV_RW == 0) || (mix_FreeChunk == 0) || (mix_PlayChannelTimed == 0)) {
			qWarning("Unable to load SDL_mixer");
			sdl_Quit();
			return;
		}
		if (mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
			qWarning("Unable to initialize SDL_mixer: %s", mix_GetError());
			sdl_Quit();
			return;
		}

		f_sdl_loaded = true;
	}
