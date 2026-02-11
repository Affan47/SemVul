sort_init_qs(sort_t * sort, board_t * board, const attack_t * attack, bool check) {

   ASSERT(sort!=NULL);
   ASSERT(board!=NULL);
   ASSERT(attack!=NULL);
   ASSERT(check==true||check==false);

   sort->board = board;
   sort->attack = attack;

   if (ATTACK_IN_CHECK(sort->attack)) {
      sort->gen = PosEvasionQS;
   } else if (check) {
      sort->gen = PosCheckQS;
   } else {
      sort->gen = PosCaptureQS;
   }

   LIST_CLEAR(sort->list);
   sort->pos = 0;
}
