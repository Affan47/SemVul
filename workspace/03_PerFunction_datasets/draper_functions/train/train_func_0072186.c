fluid_rvoice_mixer_render(fluid_rvoice_mixer_t* mixer, int blockcount)
{
	fluid_profile_ref_var(prof_ref);

	mixer->current_blockcount = blockcount > mixer->buffers.buf_blocks ?
	                            mixer->buffers.buf_blocks : blockcount;


	fluid_mixer_buffers_zero(&mixer->buffers);
	fluid_profile(FLUID_PROF_ONE_BLOCK_CLEAR, prof_ref);

#ifdef ENABLE_MIXER_THREADS
	if (mixer->thread_count > 0)
		fluid_render_loop_multithread(mixer);
	else
#endif
		fluid_render_loop_singlethread(mixer);
	fluid_profile(FLUID_PROF_ONE_BLOCK_VOICES, prof_ref);


	fluid_rvoice_mixer_process_fx(mixer);


	fluid_rvoice_mixer_process_finished_voices(mixer);

	return mixer->current_blockcount;
}
