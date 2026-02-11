longswapchar(char ** wlst, const char * word, int ns, int cpdsuggest)
{
   char candidate[MAXSWUTF8L];
   char * p;
   char * q;
   char tmpc;
   int wl=strlen(word);

   strcpy(candidate, word);
   for (p = candidate;  *p != 0;  p++) {
    for (q = candidate;  *q != 0;  q++) {
     if (abs((int)(p-q)) > 1) {
      tmpc = *p;
      *p = *q;
      *q = tmpc;
      ns = testsug(wlst, candidate, wl, ns, cpdsuggest, NULL, NULL);
      if (ns == -1) return -1;
      *q = *p;
      *p = tmpc;
     }
    }
   }
   return ns;
}
