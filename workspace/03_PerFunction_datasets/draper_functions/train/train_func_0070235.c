fish_sound_new (int mode, FishSoundInfo * fsinfo)
{
  FishSound * fsound;

  if (!FS_DECODE && mode == FISH_SOUND_DECODE) return NULL;

  if (!FS_ENCODE && mode == FISH_SOUND_ENCODE) return NULL;

  if (mode == FISH_SOUND_ENCODE) {
    if (fsinfo == NULL) {
      return NULL;
    } else {
      if (!(HAVE_VORBIS && HAVE_VORBISENC)) {
	if (fsinfo->format == FISH_SOUND_VORBIS) return NULL;
      }
      if (!HAVE_SPEEX) {
	if (fsinfo->format == FISH_SOUND_SPEEX) return NULL;
      }
      if (!HAVE_FLAC) {
        if (fsinfo->format == FISH_SOUND_FLAC) return NULL;
      }
    }
  } else if (mode != FISH_SOUND_DECODE) {
    return NULL;
  }

  fsound = fs_malloc (sizeof (FishSound));
  if (fsound == NULL) return NULL;

  fsound->mode = mode;
  fsound->interleave = 0;
  fsound->frameno = 0;
  fsound->next_granulepos = -1;
  fsound->next_eos = 0;
  fsound->codec = NULL;
  fsound->codec_data = NULL;
  fsound->callback.encoded = NULL;
  fsound->user_data = NULL;

  fish_sound_comments_init (fsound);

  if (mode == FISH_SOUND_DECODE) {
    fsound->info.samplerate = 0;
    fsound->info.channels = 0;
    fsound->info.format = FISH_SOUND_UNKNOWN;
  } else if (mode == FISH_SOUND_ENCODE) {
    fsound->info.samplerate = fsinfo->samplerate;
    fsound->info.channels = fsinfo->channels;
    fsound->info.format = fsinfo->format;

    if (fish_sound_set_format (fsound, fsinfo->format) == -1) {
      fs_free (fsound);
      return NULL;
    }
  }

  return fsound;
}
