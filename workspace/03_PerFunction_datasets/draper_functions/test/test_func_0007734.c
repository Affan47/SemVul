sort_init(sort_t * sort, board_t * board, const attack_t * attack, int depth, int height, int trans_killer) {

   ASSERT(sort!=NULL);
   ASSERT(board!=NULL);
   ASSERT(attack!=NULL);
   ASSERT(depth_is_ok(depth));
   ASSERT(height_is_ok(height));
   ASSERT(trans_killer==MoveNone||move_is_ok(trans_killer));

   sort->board = board;
   sort->attack = attack;

   sort->depth = depth;
   sort->height = height;

   sort->trans_killer = trans_killer;
   sort->killer_1 = Killer[sort->height][0];
   sort->killer_2 = Killer[sort->height][1];

   if (ATTACK_IN_CHECK(sort->attack)) {

      gen_legal_evasions(sort->list,sort->board,sort->attack);
      note_moves(sort->list,sort->board,sort->height,sort->trans_killer);
      list_sort(sort->list);

      sort->gen = PosLegalEvasion + 1;
      sort->test = TEST_NONE;

   } else {

      LIST_CLEAR(sort->list);
      sort->gen = PosSEE;
   }

   sort->pos = 0;
}
