win_kbbk(const board_t * board, int colour) {

   int me, opp;
   int att, def;
   int dist;
   int value;

   ASSERT(board!=NULL);
   ASSERT(colour==White||colour==Black);

   ASSERT(board->piece_nb==4);
   ASSERT(board->pawn_size[White]==0);
   ASSERT(board->pawn_size[Black]==0);
   ASSERT(board->square[board->piece[colour][1]]==(BishopFlag|COLOUR_FLAG(colour)));
   ASSERT(board->square[board->piece[colour][2]]==(BishopFlag|COLOUR_FLAG(colour)));


   me = colour;
   opp = COLOUR_OPP(me);
   att = KING_POS(board,me);
   def = KING_POS(board,opp);
   dist = DISTANCE(att,def);
   value = ValueWin;


   if (SQUARE_COLOUR(board->piece[colour][1]) == SQUARE_COLOUR(board->piece[colour][2])) return 0;


   value += MinPst[SQUARE_TO_64(def)];


   value += 80 - (dist * 10);

   if (COLOUR_IS_BLACK(me)) value = -value;

   ASSERT(value!=0);
   ASSERT(!value_is_mate(value));

   return value;
}
