fc_utf8_strlen(const char *utf8_string)
{
  size_t len;

  fc_assert_ret_val(NULL != utf8_string, 0);

  for (len = 0; '\0' != *utf8_string; len++) {
    utf8_string = fc_ut8_next_char(utf8_string);
  }
  return len;
}
