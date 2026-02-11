advance_time(int frames)
{
	audio_timer += (double)frames * 1000.0 / (double)a_settings.samplerate;
	if(audio_timer >= 2147483648.0)
		audio_timer -= 4294967296.0;
}
