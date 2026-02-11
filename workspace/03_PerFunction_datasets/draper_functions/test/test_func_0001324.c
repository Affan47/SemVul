parse_precomment(s)
char* s;

{
  char package[40];
  char *p;

  if (*s == '%') {
    p = s+1;
    readstr(package, &p, 40);
    event_specific(package, p);
  } else {
    event_comment(s);
  };
}
