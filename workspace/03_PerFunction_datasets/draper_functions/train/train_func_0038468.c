val_decimal(my_decimal *decimal_value)
{
  if (null_value)
    return 0;
  int2my_decimal(E_DEC_FATAL_ERROR, value, unsigned_flag, decimal_value);
  return (decimal_value);
}
