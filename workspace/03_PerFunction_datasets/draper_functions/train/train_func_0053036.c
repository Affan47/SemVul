zsound_effect(void)
{
#ifdef GARGLK
  uint8_t repeats, volume;
  static uint32_t vols[8] = {
    0x02000, 0x04000, 0x06000, 0x08000,
    0x0a000, 0x0c000, 0x0e000, 0x10000
  };

  if(sound_channel == NULL || zargs[0] < 3) return;

  repeats = zargs[2] >> 8;
  volume = zargs[2] & 0xff;

  if(volume == 0) volume = 1;
  if(volume  > 8) volume = 8;

  glk_schannel_set_volume(sound_channel, vols[volume - 1]);

  switch(zargs[1])
  {
    case 1:
      glk_sound_load_hint(zargs[0], 1);
      break;
    case 2:
      glk_schannel_play_ext(sound_channel, zargs[0], repeats == 255 ? -1 : repeats, 0);
      break;
    case 3:
      glk_schannel_stop(sound_channel);
      break;
    case 4:
      glk_sound_load_hint(zargs[0], 0);
      break;
  }
#endif
}
