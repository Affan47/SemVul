mix_resume(sfx_pcm_mixer_t *self)
{
	ACQUIRE_LOCK();
	P->paused = 0;
	RELEASE_LOCK();
}
