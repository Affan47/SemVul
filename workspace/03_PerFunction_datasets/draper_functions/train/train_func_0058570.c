func (int arg)
{
  int sum = 0, i, max, arr[1024];

  if (arg == 0)
    {
      sum = global[2];
      sum += sum + sum * getppid ();
      return sum;
    }
  else
    {
      max = arg;
      if (max >= 64)
	max = 64;

      for (i = 0; i < max; ++i)
	arr[i] = func (arg - 1);

      for (i = 0; i < max; ++i)
	if (arr[i] > 16)
	  sum += arr[i];
	else
	  sum -= arr[i];
    }
  return sum;
}
