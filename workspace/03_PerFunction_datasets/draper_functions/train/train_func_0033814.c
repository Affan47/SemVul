xstr_iconveh (const char *src,
              const char *from_codeset, const char *to_codeset,
              enum iconv_ilseq_handler handler)
{
  char *result = str_iconveh (src, from_codeset, to_codeset, handler);

  if (result == NULL && errno == ENOMEM)
    xalloc_die ();
  return result;
}
