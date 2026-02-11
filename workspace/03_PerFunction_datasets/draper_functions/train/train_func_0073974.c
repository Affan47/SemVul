dc_load_game(int script, int* yield, int* preturnint, int game_slot)
{
  kill_all_scripts_for_real();
  *preturnint = load_game(game_slot);
  log_info("load completed.");
  if (rinfo[script] == NULL)
    log_error("[DinkC] Script %d is suddenly null!", script);
  *pupdate_status = 1;
  draw_status_all();
  *yield = 1;
}
