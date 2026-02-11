set_real(double num,uint decimals, CHARSET_INFO *cs)
{
  char buff[FLOATING_POINT_BUFFER];
  uint dummy_errors;
  size_t len;

  str_charset=cs;
  if (decimals >= NOT_FIXED_DEC)
  {
    len= my_gcvt(num, MY_GCVT_ARG_DOUBLE, sizeof(buff) - 1, buff, NULL);
    return copy(buff, len, &my_charset_latin1, cs, &dummy_errors);
  }
  len= my_fcvt(num, decimals, buff, NULL);
  return copy(buff, (uint32) len, &my_charset_latin1, cs,
              &dummy_errors);
}
