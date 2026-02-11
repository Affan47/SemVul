dfa_prepare_for_match(int color)
{
  int i, j;
  int pos;

  if (dfa_board_size != board_size) {
    dfa_board_size = board_size;

    for (pos = 0; pos < DFA_BASE * DFA_BASE; pos++)
      dfa_p[pos] = OUT_BOARD;
  }


  for (i = 0; i < dfa_board_size; i++)
    for (j = 0; j < dfa_board_size; j++)
      dfa_p[DFA_POS(i, j)] = EXPECTED_COLOR(color, BOARD(i, j));

  prepare_for_match(color);
}
