to_hex(int32 slen)
{
 register int32 i, bi;
 register word32 *ap, *bp;
 word32 a, b;


 ap = __acwrk;
 bp = __bcwrk;
 for (i = slen - 1, bi = 0; i >= 0; i--)
  {

   ch_tohexs(&a, &b, __numtoken[i]);
   if (bi == 0) { *ap = a; *bp = b; bi += 4; continue; }
   *ap |= a << bi;
   *bp |= b << bi;
   if (bi == 28) { bi = 0; ap++; bp++; } else bi += 4;
  }
}
