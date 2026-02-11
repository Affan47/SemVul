convert_string_directly (iconv_t cd, const char *string,
                         const struct conversion_context* context)
{
  size_t len = strlen (string) + 1;
  char *result = NULL;
  size_t resultlen = 0;

  if (xmem_cd_iconv (string, len, cd, &result, &resultlen) == 0)

    if (resultlen > 0 && result[resultlen - 1] == '\0'
        && strlen (result) == resultlen - 1)
      return result;

  conversion_error (context);

  return NULL;
}
