SDLVid_Setup(struct _video_out *dr, void *os_handle, void *os_display, u32 init_flags)
{
	SDLVID();


	ctx->os_handle = os_handle;
	ctx->is_init = 0;
	ctx->output_3d_type = 0;
	ctx->force_alpha = (init_flags & GF_TERM_WINDOW_TRANSPARENT) ? 1 : 0;

	if (!SDLOUT_InitSDL()) return GF_IO_ERR;

#ifdef	SDL_WINDOW_THREAD
	ctx->sdl_th_state = SDL_STATE_STOPPED;
	gf_th_run(ctx->sdl_th, SDLVid_EventProc, dr);

	while (!ctx->sdl_th_state)
		gf_sleep(10);

	if (ctx->sdl_th_state==SDL_STATE_STOP_REQ) {
		SDLOUT_CloseSDL();
		ctx->sdl_th_state = SDL_STATE_STOPPED;
		return GF_IO_ERR;
	}
#else
	if (!SDLVid_InitializeWindow(ctx, dr)) {
		SDLOUT_CloseSDL();
		return GF_IO_ERR;
	}
#endif

	ctx->is_init = 1;
	return GF_OK;
}
