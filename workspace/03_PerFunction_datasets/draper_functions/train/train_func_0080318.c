hook_quit(const char *str)
{
	int i;

	save_prefs();

	string_free(ANGBAND_DIR_USER_SDL);


	for (i = 0; i < ANGBAND_TERM_MAX; i++)
	{
		term_windowFree(&windows[i]);
		string_free(windows[i].req_font);
	}

#ifdef USE_GRAPHICS

	if (GfxSurface) SDL_FreeSurface(GfxSurface);
#endif

	sdl_FontFree(&SystemFont);


	sdl_WindowFree(&StatusBar);


	sdl_WindowFree(&PopUp);


	SDL_FreeSurface(AppWin);


	TTF_Quit();


	SDL_Quit();

	for (i = 0; i < MAX_FONTS; i++)
		string_free(FontList[i]);
}
