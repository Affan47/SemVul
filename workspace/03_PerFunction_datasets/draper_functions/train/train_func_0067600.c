print_tag_start(const string name)
{
  string s, h;

  if (name[0] != '{') {
    printf("<%s", name);
  } else if (name[1] == '}') {
    printf("<%s", name + 2);
  } else if (strncmp(name, XMLNS, XMLNSLEN) == 0) {
    printf("<xml:%s", name + XMLNSLEN);
  } else if (! (h = strchr(name, '}'))) {
    fprintf(stderr, "%d: Unmatched \"{\" in tag name (\"%s\")\n",
	    yylineno, name);
    has_error = true;
  } else {
    printf("<%s xmlns=\"", h + 1);
    for (s = name + 1; s != h; s++) putchar(*s);
    putchar('\"');
  }
}
