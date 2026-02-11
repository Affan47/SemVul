identitytest(OFString a, OFString b)
{
  OFString x = a;
  OFString y = b;
  x += b;
  y.insert (0, a);
  assert((a + b) == x);
  assert((a + b) == y);
  assert(x == y);

  assert((a + b + a) == (a + (b + a)));

  x.erase (x.rfind (b));
  assert(x == a);

  y.replace (0, y.rfind (b), b);
  assert(y == (b + b));
  y.replace (y.find (b), b.length (), a);
  assert(y == (a + b));
}
