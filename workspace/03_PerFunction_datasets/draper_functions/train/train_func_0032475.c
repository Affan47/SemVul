compute_divisor_lcm(Circle *p)
{
  long l = 1;

  while (p)
    {
      l = lcm(l, p->divisor);
      p = p->pchild;
    }
  return l;
}
