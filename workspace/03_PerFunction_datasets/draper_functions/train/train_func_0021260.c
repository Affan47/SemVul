pv_fill(const mv_t pv[], board_t * board) {

   int move;
   int trans_move, trans_depth, trans_min_value, trans_max_value, trans_eval;
   undo_t undo[1];

   ASSERT(pv!=NULL);
   ASSERT(board!=NULL);

   ASSERT(UseTrans);

   move = *pv;

   if (move != MoveNone && move != MoveNull) {

      move_do(board,move,undo);
      pv_fill(pv+1,board);
      move_undo(board,move,undo);

      trans_move = move;
      trans_depth = -127;
      trans_min_value = -ValueInf;
      trans_max_value = +ValueInf;

      if (board_is_check(board)) {
         trans_eval = ValueNone;
      } else {
         trans_eval = eval(board,ThreadMain);
      }

      trans_store(board->key,trans_move,trans_depth,trans_min_value,trans_max_value,trans_eval);
   }
}
