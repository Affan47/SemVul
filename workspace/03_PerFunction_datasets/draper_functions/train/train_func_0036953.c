read_audio_attr(audio_attr_t *aa) {
  getbits_state_t state;
  uint8_t buf[sizeof(audio_attr_t)];

  memcpy(buf, aa, sizeof(audio_attr_t));
  if (!dvdread_getbits_init(&state, buf)) abort();
  aa->audio_format = dvdread_getbits(&state, 3);
  aa->multichannel_extension = dvdread_getbits(&state, 1);
  aa->lang_type = dvdread_getbits(&state, 2);
  aa->application_mode = dvdread_getbits(&state, 2);
  aa->quantization = dvdread_getbits(&state, 2);
  aa->sample_frequency = dvdread_getbits(&state, 2);
  aa->unknown1 = dvdread_getbits(&state, 1);
  aa->channels = dvdread_getbits(&state, 3);
  aa->lang_code = dvdread_getbits(&state, 16);
  aa->lang_extension = dvdread_getbits(&state, 8);
  aa->code_extension = dvdread_getbits(&state, 8);
  aa->unknown3 = dvdread_getbits(&state, 8);
  aa->app_info.karaoke.unknown4 = dvdread_getbits(&state, 1);
  aa->app_info.karaoke.channel_assignment = dvdread_getbits(&state, 3);
  aa->app_info.karaoke.version = dvdread_getbits(&state, 2);
  aa->app_info.karaoke.mc_intro = dvdread_getbits(&state, 1);
  aa->app_info.karaoke.mode = dvdread_getbits(&state, 1);
}
