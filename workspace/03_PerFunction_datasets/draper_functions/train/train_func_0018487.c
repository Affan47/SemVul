fixed_convert_from_real (FIXED_VALUE_TYPE *f, enum machine_mode mode,
			 const REAL_VALUE_TYPE *a, bool sat_p)
{
  bool overflow_p = false;
  REAL_VALUE_TYPE real_value, fixed_value, base_value;
  bool unsigned_p = UNSIGNED_FIXED_POINT_MODE_P (mode);
  int i_f_bits = GET_MODE_IBIT (mode) + GET_MODE_FBIT (mode);
  unsigned int fbit = GET_MODE_FBIT (mode);
  enum fixed_value_range_code temp;

  real_value = *a;
  f->mode = mode;
  real_2expN (&base_value, fbit, mode);
  real_arithmetic (&fixed_value, MULT_EXPR, &real_value, &base_value);
  real_to_integer2 ((HOST_WIDE_INT *)&f->data.low, &f->data.high, &fixed_value);
  temp = check_real_for_fixed_mode (&real_value, mode);
  if (temp == FIXED_UNDERFLOW)
    {
      if (sat_p)
	{
	  if (unsigned_p)
	    {
	      f->data.low = 0;
	      f->data.high = 0;
	    }
	  else
	    {
	      f->data.low = 1;
	      f->data.high = 0;
	      f->data = f->data.alshift (i_f_bits, HOST_BITS_PER_DOUBLE_INT);
	      f->data = f->data.sext (1 + i_f_bits);
	    }
	}
      else
	overflow_p = true;
    }
  else if (temp == FIXED_GT_MAX_EPS || temp == FIXED_MAX_EPS)
    {
      if (sat_p)
	{
	  f->data.low = -1;
	  f->data.high = -1;
	  f->data = f->data.zext (i_f_bits);
	}
      else
	overflow_p = true;
    }
  f->data = f->data.ext ((!unsigned_p) + i_f_bits, unsigned_p);
  return overflow_p;
}
