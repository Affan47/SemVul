findMaxMin2 (sInt4 *Data, int start, int stop,
                         sInt4 li_primMiss, sInt4 li_secMiss,
                         sInt4 *min, sInt4 *max)
{
   char f_min = 0;
   int i;

   *max = *min = Data[start];
   for (i = start; i < stop; i++) {
      if ((Data[i] != li_secMiss) && (Data[i] != li_primMiss)) {
         if (!f_min) {
            *max = Data[i];
            *min = Data[i];
            f_min = 1;
         } else {
            if (*max < Data[i]) {
               *max = Data[i];
            } else if (*min > Data[i]) {
               *min = Data[i];
            }
         }
      }
   }
   return f_min;
}
