__ieee754_j0 (double x)
{
  double z, s, c, ss, cc, r, u, v, r1, r2, s1, s2, z2, z4;
  int32_t hx, ix;

  GET_HIGH_WORD (hx, x);
  ix = hx & 0x7fffffff;
  if (ix >= 0x7ff00000)
    return one / (x * x);
  x = fabs (x);
  if (ix >= 0x40000000)
    {
      __sincos (x, &s, &c);
      ss = s - c;
      cc = s + c;
      if (ix < 0x7fe00000)
	{
	  z = -__cos (x + x);
	  if ((s * c) < zero)
	    cc = z / ss;
	  else
	    ss = z / cc;
	}


      if (ix > 0x48000000)
	z = (invsqrtpi * cc) / __ieee754_sqrt (x);
      else
	{
	  u = pzero (x); v = qzero (x);
	  z = invsqrtpi * (u * cc - v * ss) / __ieee754_sqrt (x);
	}
      return z;
    }
  if (ix < 0x3f200000)
    {
      math_force_eval (huge + x);
      if (ix < 0x3e400000)
	return one;
      else
	return one - 0.25 * x * x;
    }
  z = x * x;
  r1 = z * R[2]; z2 = z * z;
  r2 = R[3] + z * R[4]; z4 = z2 * z2;
  r = r1 + z2 * r2 + z4 * R[5];
  s1 = one + z * S[1];
  s2 = S[2] + z * S[3];
  s = s1 + z2 * s2 + z4 * S[4];
  if (ix < 0x3FF00000)
    {
      return one + z * (-0.25 + (r / s));
    }
  else
    {
      u = 0.5 * x;
      return ((one + u) * (one - u) + z * (r / s));
    }
}
