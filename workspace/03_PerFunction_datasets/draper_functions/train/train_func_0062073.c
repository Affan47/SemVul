parseDec(char **s, Bit32 *value){
  enum { MAX_DEC_LEN = 4 };
  char *dec = ecalloc(MAX_DEC_LEN, sizeof(char));
  int i;
  for(i = 0; isdigit(**s) && i < MAX_DEC_LEN; (*s)++)
    dec[i++] = **s;

  if (i > 0){
    *value = atoi(dec);
    free(dec);
    return TRUE;
  }
  else
    return FALSE;
}
