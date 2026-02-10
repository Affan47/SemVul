generate2(int genMethod, int grainFactor, int randomSeed)
{
   int i,k;

   iparmx = grainFactor * 8;

   srand(randomSeed);

   recur_level = 0;

   if ( genMethod == 0)
   {
      sub_divide(0,0,max_x,max_y);
   }
   else
   {
      recur1 = i = k = 1;
      while(new_sub_divide(0,0,max_x,max_y,i)==0)
      {
         k = k * 2;
         if (k  > max_x && k > max_y)
            break;
         i++;
		}
   }
}
