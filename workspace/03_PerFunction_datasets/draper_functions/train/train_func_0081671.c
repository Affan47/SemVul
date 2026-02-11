midi_adlibemu_event(guint8 command, guint8 note, guint8 velocity, guint32 delta)
{
  guint8 channel, oper;

  channel = command & 0x0f;
  oper = command & 0xf0;

  switch (oper) {
  case 0x80:
    return adlibemu_stop_note(channel, note, velocity);
  case 0x90:
    return adlibemu_start_note(channel, note, velocity);
  case 0xe0:
    {
      int bend = (note & 0x7f) | ((velocity & 0x7f) << 7);

      adlibemu_update_pitch(channel, note, bend);
    }
  case 0xb0:
    switch (note) {
    case 0x07:
      vol[channel] = velocity;
      break;
    case 0x0a:
      pan[channel] = velocity;
      break;
    case 0x4b:
      break;
    case 0x7b:  {
      int i = 0;
      for (i=0;i<ADLIB_VOICES;i++)
	if (oper_chn[i] == channel)
	  adlibemu_stop_note(channel, oper_note[i], 0);
      break;
    }
    default:
      ;
    }
    return 0;
  case 0xd0:

    return 0;
  default:
    printf("ADLIB: Unknown event %02x\n", command);
    return 0;
  }

  return 0;
}
