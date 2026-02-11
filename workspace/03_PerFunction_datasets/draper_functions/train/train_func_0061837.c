print_attrs(const pairlist attribs)
{
  string h, s;
  pairlist p;
  int n = 0;

  for (p = attribs; p; p = p->next) {
    if (p->name[0] != '{') {
      printf(" %s=\"%s\"", p->name, p->value);
    } else if (p->name[1] == '}') {
      printf(" %s=\"%s\"", p->name + 2, p->value);
    } else if (strncmp(p->name, XMLNS, XMLNSLEN) == 0) {
      printf(" xml:%s=\"%s\"", p->name + XMLNSLEN, p->value);
    } else if (! (h = strchr(p->name, '}'))) {
      fprintf(stderr, "%d: Unmatched \"{\" in attribute name (\"%s\")\n",
	      yylineno, p->name);
      has_error = true;
    } else {
      printf(" xmlns:x%d=\"", n);
      for (s = p->name + 1; s != h; s++) putchar(*s);
      printf("\" x%d:%s=\"%s\"", n, h + 1, p->value);
    }
  }
}
