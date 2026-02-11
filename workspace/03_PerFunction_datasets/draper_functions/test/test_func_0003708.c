SDL_VIDEO_ReadConfig(char *option, char *parameters)
{
	if (strcmp(option, "SCANLINES_PERCENTAGE") == 0) {
		int value = Util_sscandec(parameters);
		if (value < 0 || value > 100)
			return FALSE;
		else {
			SDL_VIDEO_scanlines_percentage = value;
		}
	}
	else if (strcmp(option, "INTERPOLATE_SCANLINES") == 0)
		return (SDL_VIDEO_interpolate_scanlines = Util_sscanbool(parameters)) != -1;
	else if (strcmp(option, "VIDEO_VSYNC") == 0)
		return (SDL_VIDEO_vsync = Util_sscanbool(parameters)) != -1;
#if HAVE_OPENGL
	else if (strcmp(option, "VIDEO_ACCEL") == 0)
		return (currently_opengl = SDL_VIDEO_opengl = Util_sscanbool(parameters)) != -1;
	else if (SDL_VIDEO_GL_ReadConfig(option, parameters)) {
	}
#endif
	else if (SDL_VIDEO_SW_ReadConfig(option, parameters)) {
	}
	else
		return FALSE;
	return TRUE;
}
