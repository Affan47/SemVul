ffi_extract_byte_vector_readonly(s48_call_t call, s48_ref_t bv)
{
  char *buf = s48_extract_byte_vector_readonly_2(call, bv);
  int i;
  int res = 1;
  for (i = 0; i < 10; i++)
    res = res && (buf[i] == 'a');

  buf[4] = '4';
  buf[8] = '8';

  if (res)
    return s48_true_2(call);
  else
    return s48_false_2(call);
}
