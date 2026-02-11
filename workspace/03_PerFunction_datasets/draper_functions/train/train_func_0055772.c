MultifieldsEqual(
  struct multifield *segment1,
  struct multifield *segment2)
  {
   struct field *elem1;
   struct field *elem2;
   unsigned long length, i = 0;

   length = segment1->multifieldLength;
   if (length != segment2->multifieldLength)
     { return(FALSE); }

   elem1 = segment1->theFields;
   elem2 = segment2->theFields;


   while (i < length)
     {
      if (elem1[i].type != elem2[i].type)
        { return(FALSE); }

      if (elem1[i].type == MULTIFIELD)
        {
         if (MultifieldsEqual((struct multifield *) elem1[i].value,
                              (struct multifield *) elem2[i].value) == FALSE)
          { return(FALSE); }
        }
      else if (elem1[i].value != elem2[i].value)
        { return(FALSE); }

      i++;
     }
   return(TRUE);
  }
