get_fixed_sign_bit (double_int a, int i_f_bits)
{
  if (i_f_bits < HOST_BITS_PER_WIDE_INT)
    return (a.low >> i_f_bits) & 1;
  else
    return (a.high >> (i_f_bits - HOST_BITS_PER_WIDE_INT)) & 1;
}
