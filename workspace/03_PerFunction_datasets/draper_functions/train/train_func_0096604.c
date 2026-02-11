real_sqrt (REAL_VALUE_TYPE *r, enum machine_mode mode,
	   const REAL_VALUE_TYPE *x)
{
  static REAL_VALUE_TYPE halfthree;
  static bool init = false;
  REAL_VALUE_TYPE h, t, i;
  int iter, exp;


  if (real_isnegzero (x))
    {
      *r = *x;
      return false;
    }


  if (real_isneg (x))
    {
      get_canonical_qnan (r, 0);
      return false;
    }


  if (real_isinf (x) || real_isnan (x))
    {
      *r = *x;
      return false;
    }

  if (!init)
    {
      do_add (&halfthree, &dconst1, &dconsthalf, 0);
      init = true;
    }


  exp = real_exponent (x);
  real_ldexp (&i, &dconst1, -exp/2);


  for (iter = 0; iter < 16; iter++)
    {

      do_multiply (&t, x, &i);
      do_multiply (&h, &t, &i);
      do_multiply (&t, &h, &dconsthalf);
      do_add (&h, &halfthree, &t, 1);
      do_multiply (&t, &i, &h);


      if (iter >= 6 && real_identical (&i, &t))
	break;


      i = t;
    }


  do_multiply (&t, x, &i);
  do_multiply (&h, &t, &i);
  do_add (&i, &dconst1, &h, 1);
  do_multiply (&h, &t, &i);
  do_multiply (&i, &dconsthalf, &h);
  do_add (&h, &t, &i, 0);


  real_convert (r, mode, &h);
  return true;
}
