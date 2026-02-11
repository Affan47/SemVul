find_zero_transition(int *buf, int len, int min, int max)
{
  int a;
  int zero = (min + max) / 2;

  if (min == 40000)
    return 0;

  for (a = 0;a < len;a++)
    {
      if ((buf[a] <= zero) && (buf[a + 1] > zero))
	return len - a;
      if ((buf[a] >= zero) && (buf[a + 1] < zero))
	return len - a;
    }

  return len / 2;
}
