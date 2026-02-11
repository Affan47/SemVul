DoString(
  char *str,
  int pos,
  int *complete)
  {
   int inchar;


   inchar = str[pos];
   while (inchar  != '"')
     {


      if (inchar == '\\')
        {
         pos++;
         inchar = str[pos];
        }


      if (inchar == EOS)
        {
         *complete = FALSE;
         return(pos);
        }


      pos++;
      inchar = str[pos];
     }


   pos++;
   *complete = TRUE;
   return(pos);
  }
