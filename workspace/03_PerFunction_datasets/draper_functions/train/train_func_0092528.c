to_oct(int32 slen)
{
 register int32 i, bi;
 word32 a, b;


 for (i = slen - 1, bi = 0; i >= 0; i--, bi += 3)
  {
   ch_toocts(&a, &b, __numtoken[i]);

   __lhspsel(__acwrk, bi, &a, 3);
   __lhspsel(__bcwrk, bi, &b, 3);
  }
}
