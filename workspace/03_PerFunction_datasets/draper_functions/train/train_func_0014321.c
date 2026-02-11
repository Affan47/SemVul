HashSymbol(
  char *word,
  unsigned long range)
  {
   register int i;
   unsigned long tally = 0;

   for (i = 0; word[i]; i++)
     { tally = tally * 127 + word[i]; }

   return(tally % range);
  }
