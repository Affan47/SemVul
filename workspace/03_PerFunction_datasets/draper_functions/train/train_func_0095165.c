move_from_san_debug(const char string[], const board_t * board) {

   list_t list[1];
   int i, move;
   char move_string[256];

   ASSERT(string!=NULL);
   ASSERT(board_is_ok(board));

   gen_legal_moves(list,board);

   for (i = 0; i < list_size(list); i++) {
      move = list_move(list,i);
      if (!move_to_san(move,board,move_string,256)) ASSERT(false);
      if (my_string_equal(move_string,string)) return move;
   }

   return MoveNone;
}
