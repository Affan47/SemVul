draw_knpk(const int list[], int turn) {

   int wk, wn, wp, bk;

   ASSERT(list!=NULL);
   ASSERT(COLOUR_IS_OK(turn));


   wk = *list++;
   ASSERT(SQUARE_IS_OK(wk));

   wn = *list++;
   ASSERT(SQUARE_IS_OK(wn));

   wp = *list++;
   ASSERT(SQUARE_IS_OK(wp));
   ASSERT(SQUARE_FILE(wp)<=FileD);

   bk = *list++;
   ASSERT(SQUARE_IS_OK(bk));

   ASSERT(*list==SquareNone);


   if (wp == A7 && DISTANCE(bk,A8) <= 1) return true;

   return false;
}
