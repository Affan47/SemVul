fish_sound_command (FishSound * fsound, int command, void * data, int datasize)
{
  FishSoundInfo * fsinfo = (FishSoundInfo *)data;
  int * pi = (int *)data;

  if (fsound == NULL) return -1;

  switch (command) {
  case FISH_SOUND_GET_INFO:
    memcpy (fsinfo, &fsound->info, sizeof (FishSoundInfo));
    break;
  case FISH_SOUND_GET_INTERLEAVE:
    *pi = fsound->interleave;
    break;
  case FISH_SOUND_SET_INTERLEAVE:
    fsound->interleave = (*pi ? 1 : 0);
    break;
  default:
    if (fsound->codec && fsound->codec->command)
      return fsound->codec->command (fsound, command, data, datasize);
    break;
  }

  return 0;
}
