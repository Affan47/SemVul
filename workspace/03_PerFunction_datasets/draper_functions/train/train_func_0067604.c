dh_sizes(int *low, int *high)
{
   int x;
   LTC_ARGCHK(low != NULL);
   LTC_ARGCHK(high != NULL);
   *low  = INT_MAX;
   *high = 0;
   for (x = 0; sets[x].size != 0; x++) {
       if (*low > sets[x].size)  *low  = sets[x].size;
       if (*high < sets[x].size) *high = sets[x].size;
   }
}
