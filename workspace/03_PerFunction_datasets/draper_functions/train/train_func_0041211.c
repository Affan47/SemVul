fish_sound_set_encoded_callback (FishSound * fsound,
				 FishSoundEncoded encoded,
				 void * user_data)
{
  if (fsound == NULL) return -1;

#if FS_ENCODE
  fsound->callback.encoded = encoded;
  fsound->user_data = user_data;
#else
  return FISH_SOUND_ERR_DISABLED;
#endif

  return 0;
}
