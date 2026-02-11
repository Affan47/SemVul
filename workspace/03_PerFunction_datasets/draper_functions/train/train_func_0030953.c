getSmallest(const fltSemantics &Sem, bool Negative) {
  APFloat Val(Sem, fcNormal, Negative);


  Val.exponent = Sem.minExponent;
  Val.zeroSignificand();
  Val.significandParts()[0] = 1;
  return Val;
}
