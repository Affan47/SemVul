dj_set_sfx_channel_volume(char channel_num, char volume)
{
	if (main_info.no_sound)
		return;

	SDL_LockAudio();
	updateSoundParams(channel_num, volume*2);
	SDL_UnlockAudio();
}
