real_identical (const REAL_VALUE_TYPE *a, const REAL_VALUE_TYPE *b)
{
  int i;

  if (a->class != b->class)
    return false;
  if (a->sign != b->sign)
    return false;

  switch (a->class)
    {
    case rvc_zero:
    case rvc_inf:
      return true;

    case rvc_normal:
      if (a->exp != b->exp)
	return false;
      break;

    case rvc_nan:
      if (a->signalling != b->signalling)
	return false;

      if (a->canonical || b->canonical)
	return a->canonical == b->canonical;
      break;

    default:
      abort ();
    }

  for (i = 0; i < SIGSZ; ++i)
    if (a->sig[i] != b->sig[i])
      return false;

  return true;
}
