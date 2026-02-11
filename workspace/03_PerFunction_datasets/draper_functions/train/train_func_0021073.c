clear_screen(void)
{
#ifdef HAVE_LIBGL
	if (use_open_gl) {
		glClear(GL_COLOR_BUFFER_BIT);
		return;
	}
#endif

	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 0, 0));
}
