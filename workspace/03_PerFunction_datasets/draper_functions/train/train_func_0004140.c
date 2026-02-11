decimal_precision() const
{
  int arg0_int_part= args[0]->decimal_int_part();
  int arg1_int_part= args[1]->decimal_int_part();
  int max_int_part= max(arg0_int_part, arg1_int_part);
  int precision= max_int_part + decimals;
  return min(precision, DECIMAL_MAX_PRECISION);
}
