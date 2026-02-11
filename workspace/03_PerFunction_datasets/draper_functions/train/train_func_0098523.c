parse_string(ESL_SQNCBI_DATA *ncbi, char **str, int *len)
{
  int n;

  unsigned char  x;
  unsigned char  c;
  unsigned char *ptr;

  if (parse_expect(ncbi, "\x1a", 1) != eslOK)  return eslEFORMAT;


  if (parse_consume(ncbi, &c, 1) != eslOK)     return eslEFORMAT;
  if (c < 128) {
    n = c;
  } else {
    c = c & 0x7f;
    if (c > sizeof(n))                                 return eslEFORMAT;

    n = 0;
    while (c > 0) {
      if (parse_consume(ncbi, &x, 1) != eslOK) return eslEFORMAT;
      n = (n << 8) + (unsigned int) x;
      --c;
    }
  }


  ptr = ncbi->hdr_ptr;
  if (parse_advance(ncbi, n) != eslOK)         return eslEFORMAT;


  if (str != NULL && len == NULL) return eslEINCOMPAT;
  if (len != NULL) *len = n;
  if (str != NULL) *str = (char *)ptr;

  return eslOK;
}
