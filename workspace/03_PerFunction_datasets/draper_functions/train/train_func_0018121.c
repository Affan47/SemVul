fGetDescr(FILE *fp, lDescr *dp)
{
   char s[READ_LINE_LENGHT + 1];
   int mt, nm;
   char bra[2], comma[2], ket[2];

   DENTER(CULL_LAYER, "fGetDescr");

   if (!fp) {
      LERROR(LEFILENULL);
      DEXIT;
      return -1;
   }

   if (!dp) {
      LERROR(LEDESCRNULL);
      DEXIT;
      return -1;
   }

   if (fGetLine(fp, s, READ_LINE_LENGHT)) {
      LERROR(LEFGETLINE);
      DEXIT;
      return -1;
   }


   if (sscanf(s, "%1s %d %1s %d %1s", bra, &nm, comma, &mt, ket) != 5) {
      LERROR(LESSCANF);
      DEXIT;
      return -1;
   }

   if (bra[0] != '{' || comma[0] != ',' || ket[0] != '}') {
      LERROR(LESYNTAX);
      DEXIT;
      return -1;
   }

   dp->nm = nm;
   dp->mt = mt;
   dp->ht = NULL;

   DEXIT;
   return 0;
}
