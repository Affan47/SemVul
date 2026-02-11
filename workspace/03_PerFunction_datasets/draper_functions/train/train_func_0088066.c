decNumberOr(decNumber *res, const decNumber *lhs,
			const decNumber *rhs, decContext *set) {
  const Unit *ua, *ub;
  const Unit *msua, *msub;
  Unit	*uc, *msuc;
  Int	msudigs;
  #if DECCHECK
  if (decCheckOperands(res, lhs, rhs, set)) return res;
  #endif

  if (lhs->exponent!=0 || decNumberIsSpecial(lhs) || decNumberIsNegative(lhs)
   || rhs->exponent!=0 || decNumberIsSpecial(rhs) || decNumberIsNegative(rhs)) {
    decStatus(res, DEC_Invalid_operation, set);
    return res;
    }

  ua=lhs->lsu;
  ub=rhs->lsu;
  uc=res->lsu;
  msua=ua+D2U(lhs->digits)-1;
  msub=ub+D2U(rhs->digits)-1;
  msuc=uc+D2U(set->digits)-1;
  msudigs=MSUDIGITS(set->digits);
  for (; uc<=msuc; ua++, ub++, uc++) {
    Unit a, b;
    if (ua>msua) a=0;
     else a=*ua;
    if (ub>msub) b=0;
     else b=*ub;
    *uc=0;
    if (a|b) {
      Int i, j;

      for (i=0; i<DECDPUN; i++) {
	if ((a|b)&1) *uc=*uc+(Unit)powers[i];
	j=a%10;
	a=a/10;
	j|=b%10;
	b=b/10;
	if (j>1) {
	  decStatus(res, DEC_Invalid_operation, set);
	  return res;
	  }
	if (uc==msuc && i==msudigs-1) break;
	}
      }
    }

  res->digits=decGetDigits(res->lsu, uc-res->lsu);
  res->exponent=0;
  res->bits=0;
  return res;
  }
