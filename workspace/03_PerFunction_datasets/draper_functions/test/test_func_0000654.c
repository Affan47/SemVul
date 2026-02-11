__cbrt (double x)
{
  double xm, ym, u, t2;
  int xe;


  xm = __frexp (fabs (x), &xe);


  if (xe == 0 && fpclassify (x) <= FP_ZERO)
    return x + x;

  u = (0.354895765043919860
       + ((1.50819193781584896
	   + ((-2.11499494167371287
	       + ((2.44693122563534430
		   + ((-1.83469277483613086
		       + (0.784932344976639262 - 0.145263899385486377 * xm)
	                  * xm)
		      * xm))
		  * xm))
	      * xm))
	  * xm));

  t2 = u * u * u;

  ym = u * (t2 + 2.0 * xm) / (2.0 * t2 + xm) * factor[2 + xe % 3];

  return __ldexp (x > 0.0 ? ym : -ym, xe / 3);
}
