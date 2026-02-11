my_init(void)
{

  const int audio_rate = MIX_DEFAULT_FREQUENCY;
  const int audio_format = MIX_DEFAULT_FORMAT;
  const int audio_channels = 2;
  int i;

  if (init_sdl_audio() < 0) {
    return FALSE;
  }

  if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, buf_size) < 0) {
    log_error("Error calling Mix_OpenAudio");

    quit_sdl_audio();
    return FALSE;
  }

  Mix_AllocateChannels(MIX_CHANNELS);
  for (i = 0; i < MIX_CHANNELS; i++) {
    samples[i].wave = NULL;
  }

  my_set_volume(my_volume);
  return TRUE;
}
