mppgcd(GEN a, GEN b)
{
  if (typ(a) != t_INT || typ(b) != t_INT) err(arither1);
  return gcdii(a,b);
}
