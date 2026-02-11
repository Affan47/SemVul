getSmallestNormalized(const fltSemantics &Sem, bool Negative) {
  APFloat Val(Sem, fcNormal, Negative);


  Val.exponent = Sem.minExponent;
  Val.zeroSignificand();
  Val.significandParts()[partCountForBits(Sem.precision)-1] |=
    (((integerPart) 1) << ((Sem.precision % integerPartWidth) - 1));

  return Val;
}
