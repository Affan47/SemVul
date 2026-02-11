val_real_from_decimal()
{

  double result;
  my_decimal value_buff, *dec_val= val_decimal(&value_buff);
  if (null_value)
    return 0.0;
  my_decimal2double(E_DEC_FATAL_ERROR, dec_val, &result);
  return result;
}
