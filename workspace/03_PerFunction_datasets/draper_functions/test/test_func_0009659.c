extrachar_utf(char** wlst, const w_char * word, int wl, int ns, int cpdsuggest)
{
   char   candidate[MAXSWUTF8L];
   w_char candidate_utf[MAXSWL];
   w_char * p;
   w_char tmpc = W_VLINE;
   if (wl < 2) return ns;

   memcpy(candidate_utf, word, wl * sizeof(w_char));
   for (p = candidate_utf + wl - 1;  p >= candidate_utf; p--) {
       w_char tmpc2 = *p;
       if (p < candidate_utf + wl - 1) *p = tmpc;
       u16_u8(candidate, MAXSWUTF8L, candidate_utf, wl - 1);
       ns = testsug(wlst, candidate, strlen(candidate), ns, cpdsuggest, NULL, NULL);
       if (ns == -1) return -1;
       tmpc = tmpc2;
   }
   return ns;
}
