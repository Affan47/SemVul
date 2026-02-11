dsp_core_shutdown(dsp_core_t *dsp_core)
{
#if DEBUG
	fprintf(stderr, "Dsp: core shutdown\n");
#endif

	dsp_core->running = 0;

	if (dsp_core->thread) {
		dsp_core->resumeThread(dsp_core);
		SDL_WaitThread(dsp_core->thread, NULL);
		dsp_core->thread = NULL;
	}


	if (dsp_core->semaphore) {
		SDL_DestroySemaphore(dsp_core->semaphore);
		dsp_core->semaphore = NULL;
	}


	if (dsp_core->mutex) {
		SDL_DestroyMutex(dsp_core->mutex);
		dsp_core->mutex = NULL;
	}
}
