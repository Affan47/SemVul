settings_game_reset(void)
{
  if (!game.server.settings_gamestart_valid) {
    log_debug("No saved settings from the game start available.");
    return FALSE;
  }

  settings_iterate(SSET_ALL, pset) {
    setting_game_restore(pset);
  } settings_iterate_end;

  return TRUE;
}
