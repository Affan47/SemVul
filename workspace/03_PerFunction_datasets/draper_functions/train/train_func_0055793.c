SetSoundFXVolume(float NewVolume)
{
	if (!sound_on)
		return;
	remove_all_samples_from_WAV_cache();
}
