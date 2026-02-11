note_moves_simple(list_t * list, const board_t * board) {

   int size;
   int i, move;

   ASSERT(list_is_ok(list));
   ASSERT(board!=NULL);

   size = LIST_SIZE(list);

   if (size >= 2) {
      for (i = 0; i < size; i++) {
         move = LIST_MOVE(list,i);
         list->value[i] = move_value_simple(move,board);
      }
   }
}
