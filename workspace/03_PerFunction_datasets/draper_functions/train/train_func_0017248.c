readport_internal( libspectrum_word port )
{
  struct peripheral_data_t callback_info;


  if( debugger_mode != DEBUGGER_MODE_INACTIVE )
    debugger_check( DEBUGGER_BREAKPOINT_TYPE_PORT_READ, port );


  if( rzx_playback ) {

    libspectrum_error error;
    libspectrum_byte value;

    error = libspectrum_rzx_playback( rzx, &value );
    if( error ) {
      rzx_stop_playback( 1 );


      event_add( tstates, event_type_null );
      return readport_internal( port );
    }

    return value;
  }


  callback_info.port = port;
  callback_info.attached = 0;
  callback_info.value = 0xff;

  g_slist_foreach( ports, read_peripheral, &callback_info );

  if( !callback_info.attached )
    callback_info.value = machine_current->unattached_port();


  if( rzx_recording ) rzx_store_byte( callback_info.value );

  return callback_info.value;
}
