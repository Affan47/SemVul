run_all_commands (sc_gameref_t game, const sc_char *string)
{
  const sc_prop_setref_t bundle = gs_get_bundle (game);
  sc_bool status;


  status = run_game_commands_in_parser_context (game, string, FALSE);
  if (!status)
    status = run_priority_commands (game, string);
  if (!status)
    status = run_game_commands_in_parser_context (game, string, TRUE);
  if (!status)
    status = run_standard_commands (game, string);


  if (status && !game->is_admin)
    {
      sc_vartype_t vt_key;
      sc_int version;


      vt_key.string = "Version";
      version = prop_get_integer (bundle, "I<-s", &vt_key);
      if (version == TAF_VERSION_400)
        run_game_functions (game, string);
    }

  return status;
}
