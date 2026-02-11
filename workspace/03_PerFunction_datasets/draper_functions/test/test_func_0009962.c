new_Blip_Synth( void )
{
  Blip_Synth *ret;

  ret = malloc( sizeof( Blip_Synth ) );
  if( ret ) {
    blip_synth_init( ret );
    if( !ret->impulses ) {
      free( ret );
      return NULL;
    }
  }
  return ret;
}
