setrule(const char *s) {
   if ((int)strlen(s) + 10 > MAXRULESIZE)
      return "Rule too long for Generations" ;


   const char *p = s ;
   int tstaybits = 0, tbornbits = 0, tnumstates = 0 ;
   while ('0' <= *p && *p <= '8') {
      tstaybits |= 1<<(*p-'0') ;
      p++ ;
   }
   if (*p != '/')
      return "Missing expected slash in Generations rule" ;
   p++ ;
   while ('1' <= *p && *p <= '8') {
      tbornbits |= 1<<(*p-'0') ;
      p++ ;
   }
   if (*p != '/')
      return "Missing expected slash in Generations rule" ;
   p++ ;
   while ('0' <= *p && *p <= '9') {
      tnumstates = 10 * tnumstates + *p - '0' ;
      p++ ;
      if (tnumstates > 256)
         return "Number of states too high in Generations rule" ;
   }
   if (tnumstates < 2)
      return "Number of states too low in Generations rule" ;

   if (*p == ':') {

      const char* err = setgridsize(p) ;
      if (err) return err ;
   } else {
      if (*p) return "Unexpected stuff at end of Generations rule" ;
      gridwd = 0 ;
      gridht = 0 ;
   }

   staybits = tstaybits ;
   bornbits = tbornbits ;
   maxCellStates = tnumstates ;


   int i, j = 0 ;
   char states[4] ;
   for (i=0; i<=8; i++) {
      if (staybits & (1 << i)) canonrule[j++] = (char)('0' + i) ;
   }
   canonrule[j++] = '/' ;
   for (i=1; i<=8; i++) {
      if (bornbits & (1 << i)) canonrule[j++] = (char)('0' + i) ;
   }
   canonrule[j++] = '/' ;
   sprintf(states, "%d", tnumstates) ;
   i = 0 ;
   while (states[i]) {
      canonrule[j++] = states[i++] ;
   }
   if (gridwd > 0 || gridht > 0) {

      const char* bounds = canonicalsuffix() ;
      i = 0 ;
      while (bounds[i]) {
         canonrule[j++] = bounds[i++] ;
      }
   }
   canonrule[j] = 0 ;

   ghashbase::setrule(canonrule) ;
   return 0 ;
}
