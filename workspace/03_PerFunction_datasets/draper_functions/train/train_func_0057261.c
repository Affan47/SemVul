_init_processing(audio_wave_t *w)
{
	s_w = w;

	s_fs = (float)w->rate;
	s_dt = 1.0f / s_fs;

	s_rpos = s_wpos = 0;

	switch(s_w->format)
	{
	  case AF_STEREO8:
	  case AF_STEREO16:
	  case AF_STEREO32:
		s_stereo = 1;
		break;
	  case AF_MONO8:
	  case AF_MONO16:
	  case AF_MONO32:
	  case AF_MIDI:
		s_stereo = 0;
		break;
	}
}
