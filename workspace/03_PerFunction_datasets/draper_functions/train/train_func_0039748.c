double_2_comp2_t(double value)
{
  double mantissa;
  int exponent, exp;
  comp2_t mant;

  mantissa = frexp (value, &exponent);
  if (exponent <= MANTSIZE2)
    {

      exp = 0;
    }
  else
    {

      exp = exponent - MANTSIZE2;
    }
  mant = (comp2_t) (ldexp (mantissa, exponent - exp) + 0.5);
  if (mant > MAXMANT2)
    {

      mant >>= EXPBASE2;
      exp++;
    }
  if (exp >= MAXEXP2)
    {

      return MAXCOMP2_T;
    }
  if (mant > (MAXMANT2 / 2))
    {

      mant &= (MAXMANT2 >> 1);
      exp++;
    }

  return (mant | (exp << (MANTSIZE2 - 1)));
}
