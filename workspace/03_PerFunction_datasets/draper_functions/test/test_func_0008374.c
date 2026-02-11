InventoryParseTime (char *is, double *AnsTime)
{


   short int si_temp;


   MEMCPY_BIG (&si_temp, is + 0, sizeof (short int));
   if ((si_temp < 1900) || (si_temp > 2100)) {
      return -1;
   }
   if ((is[2] > 12) || (is[3] == 0) || (is[3] > 31) || (is[4] > 24) ||
       (is[5] > 60) || (is[6] > 61)) {
      return -1;
   }
   Clock_ScanDate (AnsTime, si_temp, is[2], is[3]);
   *AnsTime += is[4] * 3600. + is[5] * 60. + is[6];


   return 0;
}
