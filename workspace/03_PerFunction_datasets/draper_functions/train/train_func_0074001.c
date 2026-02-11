cand_abs_increment (slsr_cand_t c)
{
  double_int increment = cand_increment (c);

  if (!address_arithmetic_p && increment.is_negative ())
    increment = -increment;

  return increment;
}
