fGetBool(FILE *fp, lBool *cp)
{
   char s[READ_LINE_LENGHT + 1];
   int i = 0;

   DENTER(CULL_LAYER, "fGetBool");

   if (!fp) {
      LERROR(LEFILENULL);
      DEXIT;
      return -1;
   }

   if (fGetLine(fp, s, READ_LINE_LENGHT)) {
      LERROR(LEFGETLINE);
      DEXIT;
      return -1;
   }

   if (sscanf(s, "%d", &i) != 1) {
      LERROR(LESSCANF);
      DEXIT;
      return -1;
   }

   *cp = i;

   DEXIT;
   return 0;
}
