__get_cor_range(register int32 oi1, union intptr_u oi2,
 register int32 *i1, register int32 *i2)
{
 register word32 *wp;

 if (oi1 != -2) { *i1 = oi1; *i2 = oi2.i; }
 else
  {

   wp = &(__contab[oi2.xvi]);
   *i1 = *i2 = (int32) wp[2*__inum];
  }
}
