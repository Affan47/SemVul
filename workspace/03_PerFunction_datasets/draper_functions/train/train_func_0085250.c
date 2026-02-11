operator/(const Term &b)const
{
  return Term(c*b.c.inverse(),Monomial(theRing,m.exponent-b.m.exponent));
}
