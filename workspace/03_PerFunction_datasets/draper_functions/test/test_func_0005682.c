ScoreQ (short side)


{
   int xside;
   int s, s1, sq, EnemyKing;
   BitBoard c;

   s = s1 = 0;


   if (board.b[side][queen] == NULLBITBOARD) {
       if (side == computer) {
         s += QUEEN_NOT_PRESENT;
       }
       return(s);
    }

   xside = 1 ^ side;
   c = board.b[side][queen];
   EnemyKing = board.king[xside];

   if ( c & pinned )
   {
	s += PINNEDQUEEN * nbits(c & pinned);
   }

   while (c)
   {
      sq = leadz (c);
      CLEARBIT (c, sq);


      s1 = CTL(sq,queen,side);

      if (distance[sq][EnemyKing] <= 2)
         s1 += QUEENNEARKING;


      if (QueenAttack(sq) & weaked[xside])
         s1 += ATAKWEAKPAWN;

      s += s1;
   }

   return (s);
}
