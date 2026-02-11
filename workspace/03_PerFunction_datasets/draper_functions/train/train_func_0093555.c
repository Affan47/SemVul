write_bits(FILE *out, int freq, int count, int *sync)
{
  int a, b;
  double fact;
  long flen = 0;

  switch (freq)
    {
    case BIT_0: fact = 120; break;
    case BIT_1: fact = 120; break;
    case BIT_S: fact = 120; break;
    default:    fact = 120; break;
    }

  for (a = 0;a < count;a++)
    {
      for (b = 0;b < 2;b++)
	{
	  while (*sync < RATE)
	    {
	      *sync += freq * 2;
	      write_bit(out);
	      flen++;
	    }
	  _value = -_value;
	  *sync -= RATE;
	}
    }

  return flen;
}
