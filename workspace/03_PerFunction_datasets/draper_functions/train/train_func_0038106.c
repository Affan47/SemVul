pv_cat(mv_t dst[], const mv_t src[], int move) {

   ASSERT(pv_is_ok(src));
   ASSERT(dst!=NULL);

   *dst++ = move;

   while ((*dst++ = *src++) != MoveNone)
      ;
}
