close_snd( void )
{
  snd_write_sound();
  if( snd_t == TYPE_WAV )
    snd_finalize_wav();
  else if( snd_t == TYPE_AU )
    snd_finalize_au();
  else if( snd_t == TYPE_AIFF )
    snd_finalize_aiff();

  if( !snd ) return;
  fclose( snd );
  snd = NULL;
}
