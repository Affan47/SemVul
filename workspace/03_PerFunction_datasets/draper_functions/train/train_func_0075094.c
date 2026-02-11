miniexp_length(miniexp_t p)
{
  int n = 0;
  bool toggle = false;
  miniexp_t q = p;
  while (miniexp_consp(p))
    {
      p = cdr(p);
      if (p == q)
        return -1;
      if ((toggle = !toggle))
        q = cdr(q);
      n += 1;
    }
  return n;
}
