move_value_simple(int move, const board_t * board) {

   int value;

   ASSERT(move_is_ok(move));
   ASSERT(board!=NULL);

   value = HistoryScore;
   if (move_is_tactical(move,board)) value = mvv_lva(move,board);

   return value;
}
