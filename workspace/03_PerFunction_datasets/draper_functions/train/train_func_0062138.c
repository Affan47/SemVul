decNumberInvert(decNumber *res, const decNumber *rhs,
			    decContext *set) {
  const Unit *ua, *msua;
  Unit	*uc, *msuc;
  Int	msudigs;
  #if DECCHECK
  if (decCheckOperands(res, DECUNUSED, rhs, set)) return res;
  #endif

  if (rhs->exponent!=0 || decNumberIsSpecial(rhs) || decNumberIsNegative(rhs)) {
    decStatus(res, DEC_Invalid_operation, set);
    return res;
    }

  ua=rhs->lsu;
  uc=res->lsu;
  msua=ua+D2U(rhs->digits)-1;
  msuc=uc+D2U(set->digits)-1;
  msudigs=MSUDIGITS(set->digits);
  for (; uc<=msuc; ua++, uc++) {
    Unit a;
    Int  i, j;
    if (ua>msua) a=0;
     else a=*ua;
    *uc=0;


    for (i=0; i<DECDPUN; i++) {
      if ((~a)&1) *uc=*uc+(Unit)powers[i];
      j=a%10;
      a=a/10;
      if (j>1) {
	decStatus(res, DEC_Invalid_operation, set);
	return res;
	}
      if (uc==msuc && i==msudigs-1) break;
      }
    }

  res->digits=decGetDigits(res->lsu, uc-res->lsu);
  res->exponent=0;
  res->bits=0;
  return res;
  }
