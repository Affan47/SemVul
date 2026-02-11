SDL_VIDEO_InitSDL(void)
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
			Log_print("SDL_INIT_VIDEO FAILED: %s", SDL_GetError());
			Log_flushlog();
			exit(-1);
	}

	SDL_WM_SetCaption(Atari800_TITLE, "Atari800");


	{
		SDL_VideoInfo const * const info = SDL_GetVideoInfo();
		desktop_resolution.width = info->current_w;
		desktop_resolution.height = info->current_h;
		SDL_VIDEO_native_bpp = info->vfmt->BitsPerPixel;
	}

#if HAVE_OPENGL
	SDL_VIDEO_GL_InitSDL();
	if (!SDL_VIDEO_opengl_available)
		currently_opengl = SDL_VIDEO_opengl = FALSE;
#endif

	SDL_EnableUNICODE(1);
}
