exact_solution_compute_final_board (ExactSolution *const es)
{
  g_assert(es);

  int i;
  GamePosition *gp, *gp_next;
  for (i = 0, gp = game_position_clone(es->solved_game_position); i < es->pv_length; i++) {
    gp_next = game_position_make_move(gp, es->pv[i]);
    game_position_free(gp);
    gp = gp_next;
  }
  es->final_board = board_clone(gp->board);
  game_position_free(gp);
}
