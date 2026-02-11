process_line(const string text, const string fname, int lineno,
			 bool *in_comment)
{
  string h = text, p, q, label = NULL, key;
  char c;


  while (*in_comment ? (p = strpbrk(h, "-{")) : (p = strpbrk(h, "[{<"))) {

    while (h != p) putchar(*(h++));

    if (strncmp(p, "-->", 3) == 0) {
      putchar(*(h++));
      *in_comment = false;
      continue;
    }
    if (strncmp(p, "<!--", 4) == 0) {
      putchar(*(h++));
      *in_comment = skip_comments;
      continue;
    }
    if (strncmp(p, "{{", 2) && strncmp(p, "[[", 2)) {
      putchar(*(h++));
      continue;
    }


    if (! (q = strstr(p + 2, *p == '[' ? "]]" : "}}"))) break;

    c = *p;

    if (marklen == 0 || strncmp(p + 2, mark, marklen) == 0) {

      p += 2 + marklen;
      key = newnstring(p, q - p);

      if (! valid_label(key)) {
	while (h != q) putchar(*(h++));
	putchar(*q); putchar(*(q+1));
      } else if (!(label = get_label(key))) {
	while (h != q) putchar(*(h++));
	putchar(*q); putchar(*(q+1));
	fprintf(stderr, "%s:%d: warning: no bib entry found for %s\n",
		fname ? fname : (string)"<stdin>", lineno, key);
      } else if (c == '[') {
	expand_ref(label);
	fprintf(aux, "%s\n", label);
      } else {
	while (h != q) putchar(*(h++));
	putchar(*q); putchar(*(q+1));
	fprintf(aux, "%s\n", label);
      }
      dispose(key);

    } else {

      while (h != q) putchar(*(h++));
      putchar(*q); putchar(*(q+1));
    }
    h = q + 2;
  }

  printf("%s", h);
}
