AppendNToString(
  void *theEnv,
  char *appendStr,
  char *oldStr,
  unsigned length,
  int *oldPos,
  unsigned *oldMax)
  {
   unsigned lengthWithEOS;


   if (appendStr[length-1] != '\0') lengthWithEOS = length + 1;
   else lengthWithEOS = length;


   if (lengthWithEOS + *oldPos > *oldMax)
     {
      oldStr = (char *) genrealloc(theEnv,oldStr,(unsigned) *oldMax,(unsigned) *oldPos + lengthWithEOS);
      *oldMax = (unsigned) *oldPos + lengthWithEOS;
     }


   if (oldStr == NULL) { return(NULL); }


   strncpy(&oldStr[*oldPos],appendStr,(STD_SIZE) length);
   *oldPos += (int) (lengthWithEOS - 1);
   oldStr[*oldPos] = '\0';


   return(oldStr);
  }
