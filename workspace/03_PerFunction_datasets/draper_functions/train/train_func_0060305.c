FindModuleSeparator(
  char *theString)
  {
   unsigned i, foundColon;

   for (i = 0, foundColon = FALSE; theString[i] != EOS; i++)
     {
      if (theString[i] == ':')
        {
         if (foundColon) return(i);
         foundColon = TRUE;
        }
      else
        { foundColon = FALSE; }
     }

   return(FALSE);
  }
