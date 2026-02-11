caml_int32_mod(value v1, value v2)
{
  int32 dividend = Int32_val(v1);
  int32 divisor = Int32_val(v2);
  if (divisor == 0) caml_raise_zero_divide();


  if (dividend == (1<<31) && divisor == -1) return caml_copy_int32(0);
#ifdef NONSTANDARD_DIV_MOD
  return caml_copy_int32(caml_safe_mod(dividend, divisor));
#else
  return caml_copy_int32(dividend % divisor);
#endif
}
