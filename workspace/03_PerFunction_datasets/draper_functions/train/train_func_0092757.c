gtp_gg_undo(char *s)
{
  int number_moves = 1;

  sscanf(s, "%d", &number_moves);

  if (number_moves < 0)
    return gtp_failure("can't undo a negative number of moves");

  if (stackp > 0 || !undo_move(number_moves))
    return gtp_failure("cannot undo");

  reset_engine();

  return gtp_success("");
}
