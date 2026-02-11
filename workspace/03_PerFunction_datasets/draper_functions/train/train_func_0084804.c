add_regexp (reglist, pattern)
     struct regexp_list **reglist;
     char const *pattern;
{
  struct regexp_list *r;
  char const *m;

  r = (struct regexp_list *) xmalloc (sizeof (*r));
  bzero (r, sizeof (*r));
  r->buf.fastmap = xmalloc (256);
  m = re_compile_pattern (pattern, strlen (pattern), &r->buf);
  if (m != 0)
    diff_error ("%s: %s", pattern, m);


  r->next = *reglist;
  *reglist = r;
}
