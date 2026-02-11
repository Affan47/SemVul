decPutInt(decNumber *res, Int in) {
  Unit *up;

  decNumberZero(res);
  if (in<=0) {
    if (in==0) return res;
     else if (in!=BADINT) {
      res->bits=DECNEG;
      in=-in;
      }
     else {
      decContext set;
      decContextDefault(&set, DEC_INIT_DECIMAL64);
      decNumberFromString(res, "-2147483648", &set);
      return res;
      }
    }

  for (up=res->lsu; in>0; up++) {
    *up=(Unit)(in%(DECDPUNMAX+1));
    in=in/(DECDPUNMAX+1);
    }
  res->digits=decGetDigits(res->lsu, up-res->lsu);
  return res;
  }
