fGetList(FILE *fp, lList **lpp)
{
   char s[READ_LINE_LENGHT + 1];

   DENTER(CULL_LAYER, "fGetList");

   if (fp == NULL) {
      LERROR(LEFILENULL);
      DEXIT;
      return -1;
   }

   if (fGetLine(fp, s, READ_LINE_LENGHT)) {
      LERROR(LEFGETLINE);
      DEXIT;
      return -1;
   }

   if (strstr(s, "empty") != NULL)
      *lpp = NULL;
   else {


      if ((*lpp = lUndumpList(fp, NULL, NULL)) == NULL) {
         LERROR(LEUNDUMPLIST);
         DEXIT;
         return -1;
      }
   }

   DEXIT;
   return 0;
}
