decNumberPlus(decNumber *res, const decNumber *rhs,
			  decContext *set) {
  decNumber dzero;
  uInt status=0;
  #if DECCHECK
  if (decCheckOperands(res, DECUNUSED, rhs, set)) return res;
  #endif

  decNumberZero(&dzero);
  dzero.exponent=rhs->exponent;
  decAddOp(res, &dzero, rhs, set, 0, &status);
  if (status!=0) decStatus(res, status, set);
  #if DECCHECK
  decCheckInexact(res, set);
  #endif
  return res;
  }
