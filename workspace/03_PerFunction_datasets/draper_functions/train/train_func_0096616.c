s_is_power_of_two(fp_digit b, int *p)
{
   int x;


   if ((b==0) || (b & (b-1))) {
      return 0;
   }

   for (x = 0; x < DIGIT_BIT; x++) {
      if (b == (((fp_digit)1)<<x)) {
         *p = x;
         return 1;
      }
   }
   return 0;
}
