__iswctype (wint_t wc, wctype_t desc)
{


  if (desc == (wctype_t) 0)
    return 0;

  return wctype_table_lookup ((const char *) desc, wc);
}
