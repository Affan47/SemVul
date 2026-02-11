read_128(char *s, uint64_t *v)
{
  int l, t;
  char save;

  l = strlen(s);
  if (l > 32) return 0;

  if (l > 16) {
    if (sscanf(s + (l-16), "%llx", (long long unsigned int *) &(v[1])) == 0) return 0;
    save = s[l-16];
    s[l-16] = '\0';
    t = sscanf(s, "%llx", (long long unsigned int *) &(v[0]));
    s[l-16] = save;
    return t;
  } else {
    v[0] = 0;
    return sscanf(s, "%llx", (long long unsigned int *)&(v[1]));
  }
  return 1;
}
