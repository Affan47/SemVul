end_quote(char *s) {
  char *qs;
  char qc;
  char *q;
  char *nl;
  qc = *s;
  qs = s;
  while (1) {
    q = strpbrk(s + 1, "\"\'");
    nl = strchr(s + 1, '\n');
    if (nl && (nl < q)) {

      if (*(nl - 1) == '\\') {
	s = nl + 1;
	continue;
      }

      return qs;
    }
    if (!q && nl) {
      return qs;
    }
    if (!q)
      return 0;
    if ((*q == qc) && (*(q - 1) != '\\'))
      return q;
    s = q;
  }
}
