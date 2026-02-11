GetYesNo (char *cmdLine, char *prompt, int dvalue, int c_size)
{
   int rval;
   char *sptr;
   char *result;

   memset (cmdLine, 0, c_size);
   printf ("%s [%s] >", prompt, dvalue == TRUE ? "*y/n" : "*n/y");
   result = fgets (cmdLine, c_size, stdin);
   sptr = strtok(cmdLine, TOKENS);

   if (sptr == NULL || strlen (sptr) == 0)
      rval = dvalue;
   else if ((0 == strcmp (cmdLine, "Yes")) ||
            (0 == strcmp (cmdLine, "y")) ||
            (0 == strcmp (cmdLine, "yes")) || (0 == strcmp (cmdLine, "YES")))
      rval = TRUE;
   else
      rval = FALSE;

   return (rval);
}
