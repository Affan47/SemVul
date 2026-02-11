Set_BG_Music_Volume(float NewVolume)
{

#ifndef HAVE_LIBSDL_MIXER
  return;
#else
  if ( !sound_on ) return;

  Mix_VolumeMusic( (int) rintf( NewVolume * MIX_MAX_VOLUME ) );

#endif
}
