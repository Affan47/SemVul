remove_stone(int pos)
{
  ASSERT1(stackp == 0, pos);
  ASSERT_ON_BOARD1(pos);
  ASSERT1(IS_STONE(board[pos]), pos);

  hashdata_invert_stone(&board_hash, pos, board[pos]);
  board[pos] = EMPTY;
  reset_move_history();
  new_position();
}
