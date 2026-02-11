debugger_event_is_registered( const char *type, const char *detail )
{
  size_t i;

  for( i = 0; i < registered_events->len; i++ ) {
    debugger_event_t event =
      g_array_index( registered_events, debugger_event_t, i );

    if( event_matches( &event, type, detail ) ) return 1;
  }

  return 0;
}
