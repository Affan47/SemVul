unconditional_move_reasons(int color)
{
  int replacement_move;
  int pos;

  for (pos = BOARDMIN; pos < BOARDMAX; pos++)
    if (board[pos] == EMPTY
	&& unconditionally_meaningless_move(pos, color, &replacement_move)) {
      if (replacement_move == NO_MOVE) {
	TRACE("%1m unconditional antisuji.\n", pos);
	add_antisuji_move(pos);
      }
      else {
	TRACE("%1m unconditionally replaced to %1m.\n", pos, replacement_move);
	add_replacement_move(pos, replacement_move, color);
      }
    }
}
