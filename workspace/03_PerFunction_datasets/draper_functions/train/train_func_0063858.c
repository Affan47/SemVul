__log2f (float x)
{
  if (__builtin_expect (islessequal (x, 0.0f), 0) && _LIB_VERSION != _IEEE_)
    {
      if (x == 0.0)
	{
	  feraiseexcept (FE_DIVBYZERO);
	  return __kernel_standard_f (x, x, 148);
	}
      else
	{
	  feraiseexcept (FE_INVALID);
	  return __kernel_standard_f (x, x, 149);
	}
    }

  return  __ieee754_log2f (x);
}
