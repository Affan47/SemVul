extrachar(char** wlst, const char * word, int ns, int cpdsuggest)
{
   char    tmpc = '\0';
   char    candidate[MAXSWUTF8L];
   char *  p;
   int wl = strlen(word);
   if (wl < 2) return ns;

   strcpy (candidate, word);
   for (p = candidate + wl - 1; p >=candidate; p--) {
      char tmpc2 = *p;
      *p = tmpc;
      ns = testsug(wlst, candidate, wl-1, ns, cpdsuggest, NULL, NULL);
      if (ns == -1) return -1;
      tmpc = tmpc2;
   }
   return ns;
}
