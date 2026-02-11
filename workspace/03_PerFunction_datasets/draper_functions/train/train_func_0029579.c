dadd(word32 *z1p, word32 *z2p, int32 y, int32 n)
{
 word32 *s1p, *s2p;
 word32 carry;
 word64 sum;

 s1p = &(z1p[y - n]);
 s2p = z2p;
 carry = 0;
 while (n--)
  {
   sum = ((word64) *s1p) + ((word64) *s2p) + ((word64) carry);
   carry = 0;
   if (sum >= BASE) { sum -= BASE; carry = 1; }
   *s1p = (word32) sum;
   ++s1p;
   ++s2p;
  }
 sum = ((word64) *s1p) + ((word64) carry);
 *s1p = (word32) sum;
}
