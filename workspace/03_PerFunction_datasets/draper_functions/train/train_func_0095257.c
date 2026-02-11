SortRoot (void)


{
   leaf *p;
   int f, t ;
   int side, xside;
   BitBoard enemyP;

   side = board.side;
   xside = 1^side;
   enemyP = board.b[xside][pawn];

   for (p = TreePtr[1]; p < TreePtr[2]; p++)
   {
      f = Value[cboard[FROMSQ(p->move)]];
      if (cboard[TOSQ(p->move)] != 0 || (p->move & PROMOTION))
      {
         t = Value[cboard[TOSQ(p->move)]];
         if (f < t)
            p->score = -1000 + t - f;
         else
            p->score = -1000 + SwapOff (p->move);
      }
      else
         p->score = -3000 + SwapOff (p->move);

      p->score += taxicab[FROMSQ(p->move)][D5] - taxicab[TOSQ(p->move)][E4];

      if ( f == ValueP ) {

        if ( (enemyP & PassedPawnMask[side][TOSQ(p->move)]) == NULLBITBOARD )
           p->score +=50;
      }
   }
}
