make_history_report(void)
{
  if (player_count() == 1) {
    return;
  }

  if (game.server.scoreturn > game.info.turn) {
    return;
  }

  game.server.scoreturn = (game.info.turn + GAME_DEFAULT_SCORETURN
                           + fc_rand(GAME_DEFAULT_SCORETURN));

  historian_generic(game.server.scoreturn % HISTORIAN_LAST);
}
