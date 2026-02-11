history_prob(int move, const board_t * board) {

   int value;
   int index;

   ASSERT(move_is_ok(move));
   ASSERT(board!=NULL);

   ASSERT(!MOVE_IS_TACTICAL(move,board));

   index = history_index(move,board);

#if DEBUG
   if (thread_number() == 1) {
      ASSERT(HistHit[index]<=HistTot[index]);
      ASSERT(HistTot[index]<HistoryMax);
   }
#endif

   value = (HistHit[index] * 16384) / HistTot[index];

   if (value > 16384) value = 16384;
   ASSERT(value>=0&&value<=16384);

   return value;
}
