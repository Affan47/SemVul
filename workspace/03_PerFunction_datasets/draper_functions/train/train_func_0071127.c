debugger_breakpoint_add_port( debugger_breakpoint_type type,
			      libspectrum_word port, libspectrum_word mask,
			      size_t ignore, debugger_breakpoint_life life,
			      debugger_expression *condition )
{
  debugger_breakpoint_value value;

  switch( type ) {
  case DEBUGGER_BREAKPOINT_TYPE_PORT_READ:
  case DEBUGGER_BREAKPOINT_TYPE_PORT_WRITE:
    break;

  default:
    ui_error( UI_ERROR_ERROR, "debugger_breakpoint_add_port given type %d",
	      type );
    fuse_abort();
  }

  value.port.port = port;
  value.port.mask = mask;

  return breakpoint_add( type, value, ignore, life, condition );
}
