make_char_set (const char * func_name)
{
  long * p;

  p = scm_gc_malloc (BYTES_PER_CHARSET, "character-set");
  memset (p, 0, BYTES_PER_CHARSET);
  SCM_RETURN_NEWSMOB (scm_tc16_charset, p);
}
