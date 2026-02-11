FuncLog2Int( Obj self, Obj integer)
{
  Int res, d;
  Int a, len;
  Int mask;
  TypLimb dmask;


  if (IS_INTOBJ(integer)) {
    a = INT_INTOBJ(integer);
    if (a < 0) a = -a;
    res = NR_SMALL_INT_BITS;
    for(res = NR_SMALL_INT_BITS - 1, mask = (Int)1 << (NR_SMALL_INT_BITS-1);
        (mask & a) == 0 && mask != (Int)0;
        mask = mask >> 1, res--);
    return INTOBJ_INT(res);
  }


  if ( IS_LARGEINT(integer) ) {
    for (len = SIZE_INT(integer); ADDR_INT(integer)[len-1] == 0; len--);


    d = 1;
    a = (TypLimb)(ADDR_INT(integer)[len-1]);
    for(dmask = (TypLimb)1 << (GMP_LIMB_BITS - 1);
        (dmask & a) == 0 && dmask != (TypLimb)0;
        dmask = dmask >> 1, d++);
    return DiffInt(ProdInt(INTOBJ_INT(len), INTOBJ_INT(GMP_LIMB_BITS)),
                   INTOBJ_INT(d));
  }
  else {
    ErrorReturnObj("Log2Int: argument must be a int, (not a %s)",
           (Int)TNAM_OBJ(integer), 0L,
           "");

    return (Obj) 0L;
  }
}
