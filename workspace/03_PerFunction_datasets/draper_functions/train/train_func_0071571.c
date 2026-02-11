debugger_event( int event_code )
{
  debugger_event_t event;
  GSList *ptr;

  if( event_code >= registered_events->len ) {
    ui_error( UI_ERROR_ERROR, "internal error: invalid debugger event %d",
	      event_code );
    fuse_abort();
  }

  event = g_array_index( registered_events, debugger_event_t, event_code );

  for( ptr = debugger_breakpoints; ptr; ptr = ptr->next ) {
    debugger_breakpoint *bp = ptr->data;
    if( bp->type != DEBUGGER_BREAKPOINT_TYPE_EVENT ) continue;

    if( event_matches( &bp->value.event, event.type, event.detail ) &&
        debugger_breakpoint_trigger( bp ) ) {
      debugger_mode = DEBUGGER_MODE_HALTED;
      debugger_command_evaluate( bp->commands );
    }
  }
}
