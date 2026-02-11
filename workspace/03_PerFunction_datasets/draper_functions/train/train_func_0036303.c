compare (const Rational& a, const Rational &b)
{
  if (isZero(a.num) && isZero(b.num))
      return 0 ;
  if (isZero(a.num))
      return -sign(b.num);
  if (isZero(b.num))
      return sign(a.num);
  if (sign(a.num) != sign(b.num))
      return (sign(a.num) == -1 ? -1 : 1 )  ;
  if (sign(a.num) > 0)
      return absCompare(a,b) ;
  else return -absCompare(a,b) ;
}
