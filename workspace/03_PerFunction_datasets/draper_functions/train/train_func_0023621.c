prolong (modif, modif1, desc1, desc2)
     unsigned char *modif;
     unsigned char *modif1;
     rdsrec_list *desc1, *desc2;
{
   register long x1, dx1, yy1, dy1, x2, dx2, y2, dy2;

   x1 = desc1->X;
   yy1 = desc1->Y;
   dx1 = desc1->DX;
   dy1 = desc1->DY;
   x2 = desc2->X;
   y2 = desc2->Y;
   dx2 = desc2->DX;
   dy2 = desc2->DY;

   if (yy1 == y2)
   {
      if (dy1 == dy2)
      {
         if (x1 < x2)
         {
            if (lgx1 >= x2)
            {


               *modif = 1;
               *modif1 = 1;
               desc2->X = x1;
               desc2->DX = lgx2 - x1;
               mark_used (desc2);
               mark_remove (desc1);
               if (!is_flattenres (desc2))
               {
                  desc2->NAME = name_transfert (desc1, desc2);
               }
            }
         }
         else
         {
            if (x2 < x1)
            {
               if (lgx2 >= x1)
               {


                  *modif = 1;
                  *modif1 = 1;
                  desc2->DX = lgx1 - x2;
                  mark_used (desc2);
                  mark_remove (desc1);
                  if (!is_flattenres (desc2))
                  {
                     desc2->NAME = name_transfert (desc1, desc2);
                  }
               }
            }
         }
      }
      return;
   }
   if (x1 == x2)
   {
      if (dx1 == dx2)
      {
         if (yy1 < y2)
         {
            if (lgy1 >= y2)
            {


               *modif = 1;
               *modif1 = 1;
               desc2->Y = yy1;
               desc2->DY = lgy2 - yy1;
               mark_used (desc2);
               mark_remove (desc1);
               if (!is_flattenres (desc2))
               {
                  desc2->NAME = name_transfert (desc1, desc2);
               }
            }
         }
         else
         {
            if (y2 < yy1)
            {
               if (lgy2 >= yy1)
               {


                  *modif = 1;
                  *modif1 = 1;
                  desc2->DY = lgy1 - y2;
                  mark_used (desc2);
                  mark_remove (desc1);
                  if (!is_flattenres (desc2))
                  {
                     desc2->NAME = name_transfert (desc1, desc2);
                  }
               }
            }
         }
      }
   }
   return;
}
