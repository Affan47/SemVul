playback_frame( void )
{
  int error, finished;
  libspectrum_snap *snap;

  error = libspectrum_rzx_playback_frame( rzx, &finished, &snap );
  if( error ) return rzx_stop_playback( 0 );

  if( finished ) {
    ui_error( UI_ERROR_INFO, "Finished RZX playback" );
    return rzx_stop_playback( 0 );
  }


  event_remove_type( sentinel_event );
  event_add( RZX_SENTINEL_TIME + tstates, sentinel_event );

  if( snap ) {
    error = snapshot_copy_from( snap );
    if( error ) return rzx_stop_playback( 0 );
  }


  rzx_instruction_count = libspectrum_rzx_instructions( rzx );
  counter_reset();

  return 0;
}
