str_append(char **src, int *len, char *suffix)
{
  int slen1;
  int slen2;

  slen1 = strlen(*src);
  slen2 = strlen(suffix);

  if (slen1 + slen2 > *len) {
    while (slen1 + slen2 > *len)
      *len *= 2;
    *src = realloc(*src, *len);
  }

  strcat(*src, suffix);
}
