real_hash (r)
     const REAL_VALUE_TYPE *r;
{
  unsigned int h;
  size_t i;

  h = r->class | (r->sign << 2);
  switch (r->class)
    {
    case rvc_zero:
    case rvc_inf:
      break;

    case rvc_normal:
      h |= r->exp << 3;


    case rvc_nan:
      if (sizeof(unsigned long) > sizeof(unsigned int))
	for (i = 0; i < SIGSZ; ++i)
	  {
	    unsigned long s = r->sig[i];
	    h ^= s ^ (s >> (HOST_BITS_PER_LONG / 2));
	  }
      else
	for (i = 0; i < SIGSZ; ++i)
	  h ^= r->sig[i];
      break;

    default:
      abort ();
    }

  return h;
}
