stringcmp(const char *A,const char *AEnd,const char *B,const char *BEnd)
{
   for (; A != AEnd && B != BEnd; A++, B++)
      if (*A != *B)
	 break;

   if (A == AEnd && B == BEnd)
      return 0;
   if (A == AEnd)
      return 1;
   if (B == BEnd)
      return -1;
   if (*A < *B)
      return -1;
   return 1;
}
