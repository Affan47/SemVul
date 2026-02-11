normalize_range_list(lList *rl, cmp_func_t cmp_func) {
   lListElem *r1, *r2, *r;
   lListElem *q1, *q2, *q;


   DENTER(TOP_LAYER, "normalize_range_list");


   for_each(r, rl) {

      r1 = lFirst(lGetList(r, TMR_begin));
      r2 = lFirst(lGetList(r, TMR_end));

      for (q = lNext(r); q; q = lNext(q)) {

         q1 = lFirst(lGetList(q, TMR_begin));
         q2 = lFirst(lGetList(q, TMR_end));


         if (in_range(r1, q, cmp_func)         ||
             (r2 && in_range(r2, q, cmp_func)) ||
             in_range(q1, r, cmp_func)         ||
             (q2 && in_range(q2, r, cmp_func)))    {


            if (cmp_func(r1, q1) > 0) {
               lSwapList(r, TMR_begin, q, TMR_begin);
            }


            if ( (q2 && !r2) || cmp_func(r2, q2)<0) {
               lSwapList(r, TMR_end, q, TMR_end);
            }


            lRemoveElem(rl, &q);


            q = r;


            r1 = lFirst(lGetList(r, TMR_begin));
            r2 = lFirst(lGetList(r, TMR_end));
         }
      }
   }

   DRETURN(0);
}
