v_render(void)
{

	if (visual_bin_depth_changed (v.bin)) {
		sdl_lock ();

		v.pluginIsGL = (visual_bin_get_depth (v.bin) == VISUAL_VIDEO_DEPTH_GL);

		sdl_create (screen->w, screen->h);
		visual_bin_sync (v.bin, 1);

		sdl_unlock ();
	}

	long ticks = -SDL_GetTicks ();

	if (v.pluginIsGL) {
		visual_bin_run (v.bin);
		SDL_GL_SwapBuffers ();
	} else {
		sdl_lock ();
		visual_video_set_buffer (v.video, screen->pixels);
		visual_bin_run (v.bin);
		sdl_unlock ();

		v.pal = visual_bin_get_palette (v.bin);
		sdl_set_pal ();
		SDL_Flip (screen);
	}

	ticks += SDL_GetTicks ();
	return ticks;
}
