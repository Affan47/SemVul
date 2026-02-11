real_exponent (const REAL_VALUE_TYPE *r)
{
  switch (r->class)
    {
    case rvc_zero:
      return 0;
    case rvc_inf:
    case rvc_nan:
      return (unsigned int)-1 >> 1;
    case rvc_normal:
      return r->exp;
    default:
      abort ();
    }
}
