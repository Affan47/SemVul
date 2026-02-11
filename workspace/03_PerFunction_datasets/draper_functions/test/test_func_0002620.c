__ctanl (__complex__ long double x)
{
  __complex__ long double res;

  if (__builtin_expect (!isfinite (__real__ x) || !isfinite (__imag__ x), 0))
    {
      if (__isinf_nsl (__imag__ x))
	{
	  __real__ res = __copysignl (0.0, __real__ x);
	  __imag__ res = __copysignl (1.0, __imag__ x);
	}
      else if (__real__ x == 0.0)
	{
	  res = x;
	}
      else
	{
	  __real__ res = __nanl ("");
	  __imag__ res = __nanl ("");

	  if (__isinf_nsl (__real__ x))
	    feraiseexcept (FE_INVALID);
	}
    }
  else
    {
      long double sinrx, cosrx;
      long double den;
      const int t = (int) ((LDBL_MAX_EXP - 1) * M_LN2l / 2);
      int rcls = fpclassify (__real__ x);


      if (__builtin_expect (rcls != FP_SUBNORMAL, 1))
	{
	  __sincosl (__real__ x, &sinrx, &cosrx);
	}
      else
	{
	  sinrx = __real__ x;
	  cosrx = 1.0;
	}

      if (fabsl (__imag__ x) > t)
	{


	  long double exp_2t = __ieee754_expl (2 * t);

	  __imag__ res = __copysignl (1.0, __imag__ x);
	  __real__ res = 4 * sinrx * cosrx;
	  __imag__ x = fabsl (__imag__ x);
	  __imag__ x -= t;
	  __real__ res /= exp_2t;
	  if (__imag__ x > t)
	    {


	      __real__ res /= exp_2t;
	    }
	  else
	    __real__ res /= __ieee754_expl (2 * __imag__ x);
	}
      else
	{
	  long double sinhix, coshix;
	  if (fabsl (__imag__ x) > LDBL_MIN)
	    {
	      sinhix = __ieee754_sinhl (__imag__ x);
	      coshix = __ieee754_coshl (__imag__ x);
	    }
	  else
	    {
	      sinhix = __imag__ x;
	      coshix = 1.0L;
	    }

	  if (fabsl (sinhix) > fabsl (cosrx) * LDBL_EPSILON)
	    den = cosrx * cosrx + sinhix * sinhix;
	  else
	    den = cosrx * cosrx;
	  __real__ res = sinrx * cosrx / den;
	  __imag__ res = sinhix * coshix / den;
	}
    }

  return res;
}
