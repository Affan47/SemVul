operator+(const CORBA::Fixed& a, const CORBA::Fixed& b)
{
  if (a.PR_negative() == b.PR_negative())
    return realAdd(a, b, a.PR_negative());

  int cmp = absCmp(a, b);

  if (cmp == 0)
    return CORBA::Fixed();
  else if (cmp > 0)
    return realSub(a, b, a.PR_negative());
  else
    return realSub(b, a, b.PR_negative());
}
