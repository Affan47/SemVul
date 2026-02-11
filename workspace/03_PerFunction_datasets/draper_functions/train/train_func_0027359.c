encode_ieee_extended (fmt, buf, r)
     const struct real_format *fmt;
     long *buf;
     const REAL_VALUE_TYPE *r;
{
  unsigned long image_hi, sig_hi, sig_lo;
  bool denormal = (r->sig[SIGSZ-1] & SIG_MSB) == 0;

  image_hi = r->sign << 15;
  sig_hi = sig_lo = 0;

  switch (r->class)
    {
    case rvc_zero:
      break;

    case rvc_inf:
      if (fmt->has_inf)
	{
	  image_hi |= 32767;


	  sig_hi = 0x80000000;
	}
      else
	{
	  image_hi |= 32767;
	  sig_lo = sig_hi = 0xffffffff;
	}
      break;

    case rvc_nan:
      if (fmt->has_nans)
	{
	  image_hi |= 32767;
	  if (HOST_BITS_PER_LONG == 32)
	    {
	      sig_hi = r->sig[SIGSZ-1];
	      sig_lo = r->sig[SIGSZ-2];
	    }
	  else
	    {
	      sig_lo = r->sig[SIGSZ-1];
	      sig_hi = sig_lo >> 31 >> 1;
	      sig_lo &= 0xffffffff;
	    }
	  if (!fmt->qnan_msb_set)
	    sig_hi ^= 1 << 30 | 1 << 29;


	  sig_hi |= 0x80000000;
	}
      else
	{
	  image_hi |= 32767;
	  sig_lo = sig_hi = 0xffffffff;
	}
      break;

    case rvc_normal:
      {
	int exp = r->exp;


	if (denormal)
	  exp = 0;
	else
	  {
	    exp += 16383 - 1;
	    if (exp < 0)
	      abort ();
	  }
	image_hi |= exp;

	if (HOST_BITS_PER_LONG == 32)
	  {
	    sig_hi = r->sig[SIGSZ-1];
	    sig_lo = r->sig[SIGSZ-2];
	  }
	else
	  {
	    sig_lo = r->sig[SIGSZ-1];
	    sig_hi = sig_lo >> 31 >> 1;
	    sig_lo &= 0xffffffff;
	  }
      }
      break;

    default:
      abort ();
    }

  if (FLOAT_WORDS_BIG_ENDIAN)
    buf[0] = image_hi << 16, buf[1] = sig_hi, buf[2] = sig_lo;
  else
    buf[0] = sig_lo, buf[1] = sig_hi, buf[2] = image_hi;
}
