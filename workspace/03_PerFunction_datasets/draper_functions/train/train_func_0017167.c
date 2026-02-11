findGroupRev0 (sInt4 *Data, int start, int stop,
                           sInt4 range, int *split, sInt4 *min, sInt4 *max)
{
   int i;

   *max = *min = Data[stop - 1];
   for (i = stop - 2; i >= start; i--) {
      if (*max < Data[i]) {
         if ((Data[i] - *min) > range) {
            *split = i + 1;
            return;
         }
         *max = Data[i];
      } else if (*min > Data[i]) {
         if ((*max - Data[i]) > range) {
            *split = i + 1;
            return;
         }
         *min = Data[i];
      }
   }
   *split = start;
}
