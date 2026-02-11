C_i_string_ci_equal_p(C_word x, C_word y)
{
  C_word n;
  char *p1, *p2;

  if(C_immediatep(x) || C_header_bits(x) != C_STRING_TYPE)
    barf(C_BAD_ARGUMENT_TYPE_ERROR, "string-ci=?", x);

  if(C_immediatep(y) || C_header_bits(y) != C_STRING_TYPE)
    barf(C_BAD_ARGUMENT_TYPE_ERROR, "string-ci=?", y);

  n = C_header_size(x);

  if(n != C_header_size(y)) return C_SCHEME_FALSE;

  p1 = (char *)C_data_pointer(x);
  p2 = (char *)C_data_pointer(y);

  while(n--) {
    if(C_tolower((int)(*(p1++))) != C_tolower((int)(*(p2++))))
      return C_SCHEME_FALSE;
  }

  return C_SCHEME_TRUE;
}
