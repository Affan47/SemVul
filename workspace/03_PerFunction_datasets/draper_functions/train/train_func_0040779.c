check_overlap(b1, b2, flag)
struct merged_motif *b1, *b2;
int flag;
{
   int left1, left2, s, over;

   if (flag == 0)
   {

      left1 = b1->leftpos[0];
      left2 = b2->leftpos[0];
      if ( (left2 >= left1 && left2 <= left1 + b1->distance) ||
	   (left1 >= left2 && left1 <= left2 + b2->distance) )
	      return(YES);
      else    return(NO);
   }
   else if (flag == 1)
   {
      left1 = b1->leftpos[0] - b1->t_loffset;
      left2 = b2->leftpos[0] - b2->t_loffset;
      if ( (left2 >= left1 && left2 <= left1 + b1->t_domain) ||
	   (left1 >= left2 && left1 <= left2 + b2->t_domain) )
	      return(YES);
      else    return(NO);
   }
   else
   {
      s = 0; over = NO;
      while (s<NumSeqs && !over)
      {
         left1 = b1->leftpos[s] - b1->t_loffset;
         left2 = b2->leftpos[s] - b2->t_loffset;
         if ( (left2 >= left1 && left2 <= left1 + b1->t_domain) ||
	      (left1 >= left2 && left1 <= left2 + b2->t_domain) )
	      over = YES;
         s++;
      }
      return(over);
   }
}
