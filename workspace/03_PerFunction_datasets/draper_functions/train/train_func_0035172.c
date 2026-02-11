ucs4ncmp(ucs4 const *s1, ucs4 const *s2, size_t n)
{
  int retval = 0;

  while (n-- > 0 && (retval = (*s1 - *s2)) && (*s1++) && (*s2++))
    ;

  return retval;
}
