FuncSetCyclotomicsLimit(Obj self, Obj NewLimit) {
  UInt ok;
  Int limit;
  UInt ulimit;
  do {
    ok = 1;
    if (!IS_INTOBJ(NewLimit)) {
      ok = 0;
      NewLimit = ErrorReturnObj("Cyclotomic Field size limit must be a small integer, not a %s ",(Int)TNAM_OBJ(NewLimit), 0L, "You can return a new value");
    } else {
      limit = INT_INTOBJ(NewLimit);
      if (limit <= 0) {
	ok = 0;
	NewLimit = ErrorReturnObj("Cyclotomic Field size limit must be positive",0L, 0L, "You can return a new value");
      } else {
	ulimit = limit;
	if (ulimit < CyclotomicsLimit) {
	  ok = 0;
	NewLimit = ErrorReturnObj("Cyclotomic Field size limit must not be less than old limit of %d",CyclotomicsLimit, 0L, "You can return a new value");
	}
#ifdef SYS_IS_64_BIT
	else if (ulimit > (1L << 32)) {
	  ok = 0;
	  NewLimit = ErrorReturnObj("Cyclotomic field size limit must be less than 2^32", 0L, 0L,  "You can return a new value");
	}
#endif

      }
    }
  } while (!ok);
  CyclotomicsLimit = ulimit;
  return (Obj) 0L;
}
