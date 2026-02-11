mcr (const mp_no *x, const mp_no *y, int p)
{
  long i;
  long p2 = p;
  for (i = 1; i <= p2; i++)
    {
      if (X[i] == Y[i])
	continue;
      else if (X[i] > Y[i])
	return 1;
      else
	return -1;
    }
  return 0;
}
