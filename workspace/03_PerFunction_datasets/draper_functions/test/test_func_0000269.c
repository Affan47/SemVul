read_heading(FILE *fp)
{
  char line[BUF_MAX], *s;
  String_buf sb = get_string_buf();
  int i = 0;

  s = fgets(line, BUF_MAX, fp);
  while (s && !substring("= end of head =", s)) {
    if (i != 0) {
      sb_append(sb, s);
    }
    i++;
    s = fgets(line, BUF_MAX, fp);
  }

  if (!s)
    fatal_error("read_heading, \"= end of head =\" not found");

  return sb;
}
