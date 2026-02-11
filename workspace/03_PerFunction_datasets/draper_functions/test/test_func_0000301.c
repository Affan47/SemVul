scm_take_locale_stringn (char *str, size_t len)
{
  SCM buf, res;

  if (len == (size_t)-1)
    len = strlen (str);
  else
    {


      str = scm_realloc (str, len+1);
      str[len] = '\0';
    }

  buf = scm_i_take_stringbufn (str, len);
  res = scm_double_cell (STRING_TAG,
                         SCM_UNPACK (buf),
                         (scm_t_bits) 0, (scm_t_bits) len);
  return res;
}
