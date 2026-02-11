gt_str_read_next_line(GtStr *s, FILE *fpin)
{
  int cc;
  char c;
  gt_assert(s && fpin);
  for (;;) {
    cc = gt_xfgetc(fpin);
    if (cc == EOF)
      return EOF;
    if (cc == '\n') {
      if ((s->length+1) * sizeof (char) > s->allocated) {
        s->cstr = gt_dynalloc(s->cstr, &s->allocated,
                              (s->length+1) * sizeof (char));
      }
      s->cstr[s->length] = '\0';
      return 0;
    }
    c = cc;
    if ((s->length+2) * sizeof (char) > s->allocated) {
      s->cstr = gt_dynalloc(s->cstr, &s->allocated,
                            (s->length+2) * sizeof (char));
    }
    s->cstr[s->length++] = c;
  }
}
