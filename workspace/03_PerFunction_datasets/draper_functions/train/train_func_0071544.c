sg_load_scenario(struct loaddata *loading)
{
  const char *buf;


  sg_check_ret();

  if (NULL == secfile_section_lookup(loading->file, "scenario")) {

    return;
  }

  buf = secfile_lookup_str_default(loading->file, "", "scenario.name");
  if (buf[0] != '\0') {
    game.scenario.is_scenario = TRUE;
    sz_strlcpy(game.scenario.name, buf);
    buf = secfile_lookup_str_default(loading->file, "",
                                     "scenario.description");
    if (buf[0] != '\0') {
      sz_strlcpy(game.scenario.description, buf);
    } else {
      game.scenario.description[0] = '\0';
    }
    game.scenario.players
      = secfile_lookup_bool_default(loading->file, TRUE, "scenario.players");

    sg_failure_ret(loading->server_state == S_S_INITIAL
                   || (loading->server_state == S_S_RUNNING
                       && game.scenario.players == TRUE),
                   "Invalid scenario definition (server state '%s' and "
                   "players are %s).",
                   server_states_name(loading->server_state),
                   game.scenario.players ? "saved" : "not saved");
  } else {
    game.scenario.is_scenario = FALSE;
  }

  if (game.scenario.is_scenario) {


    aifill(0);
  }
}
