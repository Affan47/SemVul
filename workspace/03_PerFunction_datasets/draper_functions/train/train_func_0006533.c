myvsnprintf_string(char **pdest,char *de,const char *str) {
  char	*dest = *pdest;

  while (dest < de && *str)
    *dest++ = *str++;

  *pdest = dest;
}
