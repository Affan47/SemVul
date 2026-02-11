get_entry_from_line(char *buf)
{
  char *sp;
  sp = strchr(buf, ' ');
  while(*sp == ' ') {
    sp ++;
  }
  return strdup(sp);
}
