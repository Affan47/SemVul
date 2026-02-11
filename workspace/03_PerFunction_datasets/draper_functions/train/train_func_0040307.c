id(const Complex& x)
{
  Complex c (0.F);
  if ((x.im != 0.F)||(x.re != 0.F))
    c.re = 1.F;
  return c;
}
