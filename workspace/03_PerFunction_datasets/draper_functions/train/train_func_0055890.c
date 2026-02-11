unsigned_memcmp(char *coef0, char *coef1, int size)
{
   register char *end0 = coef0 + size;

   for ( ; coef0 != end0; coef0++, coef1++)
      if (*coef0 != *coef1)
	 break;
   if (coef0 == end0)
      return(0);
   return ( (unsigned char)(*coef0) < (unsigned char)(*coef1) ? -1 : 1);
}
