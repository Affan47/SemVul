add_chain2(int delta)
{
  int i;


  if (delta <= 0)
    return 0;

  for (i = 0; i < delta; i++)
  {
    if (chain >= 10)
      add_score(tenm_pow2(10));
    else
      add_score(tenm_pow2(chain));

    chain++;
  }

  return delta;
}
