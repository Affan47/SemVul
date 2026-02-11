stringcasecmp(const char *A,const char *AEnd,const char *B,const char *BEnd)
{
   for (; A != AEnd && B != BEnd; A++, B++)
      if (tolower_ascii(*A) != tolower_ascii(*B))
	 break;

   if (A == AEnd && B == BEnd)
      return 0;
   if (A == AEnd)
      return 1;
   if (B == BEnd)
      return -1;
   if (tolower_ascii(*A) < tolower_ascii(*B))
      return -1;
   return 1;
}
