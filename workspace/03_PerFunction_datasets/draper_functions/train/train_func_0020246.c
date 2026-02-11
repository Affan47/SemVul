is_in_tolerance(u_long32 value1, u_long32 value2, int accepted_tolerance) {
   u_long32 first, second;
   int ret = 0;

   if (value1 > value2) {
      first = value1;
      second = value2;
   } else {
      first = value2;
      second = value1;
   }
   if (first/second > accepted_tolerance) {
      printf("error: tolerance is %d, expected was a max. of %d\n", (int)(first/second), accepted_tolerance);
      ret = 1;
   }
   return ret;
}
