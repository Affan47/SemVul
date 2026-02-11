simple_stalemate(const board_t * board) {

   int me, opp;
   int king;
   int opp_flag;
   int from, to;
   int capture;
   const inc_t * inc_ptr;
   int inc;

   ASSERT(board!=NULL);

   ASSERT(board_is_legal(board));
   ASSERT(!board_is_check(board));


   me = board->turn;
   if (board->piece_size[me] != 1 || board->pawn_size[me] != 0) return false;


   king = KING_POS(board,me);
   if (king != A1 && king != H1 && king != A8 && king != H8) return false;


   opp = COLOUR_OPP(me);
   opp_flag = COLOUR_FLAG(opp);


   from = king;

   for (inc_ptr = KingInc; (inc=*inc_ptr) != IncNone; inc_ptr++) {
      to = from + inc;
      capture = board->square[to];
      if (capture == Empty || FLAG_IS(capture,opp_flag)) {
         if (!is_attacked(board,to,opp)) return false;
      }
   }


   ASSERT(board_is_stalemate((board_t*)board));

   return true;
}
