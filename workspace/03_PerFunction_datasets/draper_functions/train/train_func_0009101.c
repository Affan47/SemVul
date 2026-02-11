getid()
   {
   word indx;

   indx = getstr();
   if (indx == -1)
      return EOF;
   return putident((int)strlen(&lsspace[indx])+1, 1);
   }
