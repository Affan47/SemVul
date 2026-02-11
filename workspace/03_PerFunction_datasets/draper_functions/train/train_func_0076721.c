debug_cmd_debugger (sc_gameref_t game)
{
  const sc_debuggerref_t debug = debug_get_debugger (game);


  if (debug)
    debug_dialog (game);
  else
    if_print_string ("SCARE's game debugger is not enabled.  Sorry.\n");


  game->is_admin = TRUE;
  return TRUE;
}
