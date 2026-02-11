realDiv(const CORBA::Fixed& a, const CORBA::Fixed& b, CORBA::Boolean negative)
{
  int i, ai, bi, wi, ri, digits, scale, unscale, v, ad, bd, carry = 0;


  CORBA::Octet work   [OMNI_FIXED_DIGITS * 2];
  CORBA::Octet running[OMNI_FIXED_DIGITS * 2];

  memset(work,    0, OMNI_FIXED_DIGITS * 2);
  memset(running, 0, OMNI_FIXED_DIGITS * 2);


  ad = a.fixed_digits();
  while (a.PR_val()[ad - 1] == 0) --ad;


  ri = OMNI_FIXED_DIGITS * 2 - 1;
  ai = ad - 1;
  while (ai >= 0) {
    running[ri] = a.PR_val()[ai];
    --ri;
    --ai;
  }


  bd = b.fixed_digits();
  while (b.PR_val()[bd - 1] == 0) --bd;


  unscale = (ad - a.fixed_scale()) - (bd - b.fixed_scale()) + 1;
  digits  = 0;


  if (unscale < 0)
    digits  = -unscale;

  ri = OMNI_FIXED_DIGITS * 2 - 1;
  wi = ri - digits;


  while (digits < OMNI_FIXED_DIGITS) {


    for (i=0; i < OMNI_FIXED_DIGITS*2 && running[i] == 0; ++i);
    if (i == OMNI_FIXED_DIGITS * 2)
      break;

    work[wi] = divDigit(running, OMNI_FIXED_DIGITS * 2, b.PR_val(), bd, ri);

    if (digits || work[wi])
      ++digits;

    --wi; --ri;
  }
  wi = OMNI_FIXED_DIGITS * 2 - 1;


  if (unscale >= 0) {
    while (work[wi] == 0 && unscale > 0) {
      --wi; --unscale;
    }
  }
  else
    unscale = 0;


  if (unscale > OMNI_FIXED_DIGITS) {
    OMNIORB_THROW(DATA_CONVERSION,
		  DATA_CONVERSION_RangeError, CORBA::COMPLETED_NO);
  }


  if (digits < unscale)
    digits = unscale;

  CORBA::Octet* wp = &work[wi - digits + 1];


  scale = digits - unscale;
  if (digits < scale)
    digits = scale;


  while (scale > 0 && *wp == 0) {
    ++wp; --scale; --digits;
  }

  return CORBA::Fixed(wp, digits, scale, negative);
}
