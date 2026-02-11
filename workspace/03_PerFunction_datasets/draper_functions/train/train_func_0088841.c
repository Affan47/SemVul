move_value(int move, const board_t * board, int height, int trans_killer, int thread) {

   int value;

   ASSERT(move_is_ok(move));
   ASSERT(board!=NULL);
   ASSERT(height_is_ok(height));
   ASSERT(trans_killer==MoveNone||move_is_ok(trans_killer));
   ASSERT(thread_is_ok(thread));

   if (false) {
   } else if (move == trans_killer) {
      value = TransScore;
   } else if (MOVE_IS_TACTICAL(move,board)) {
      value = capture_value(move,board);
   } else if (move == Killer[thread][height][0]) {
      value = KillerScore;
   } else if (move == Killer[thread][height][1]) {
      value = KillerScore - 1;
   } else {
      value = quiet_move_value(move,board);
   }

   return value;
}
