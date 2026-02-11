gl_tab (buf, offset, loc)
     char *buf;
     int offset;
     int *loc;

{
  int i, count, len;

  len = strlen (buf);
  count = 8 - (offset + *loc) % 8;
  for (i = len; i >= *loc; i--)
    buf[i + count] = buf[i];
  for (i = 0; i < count; i++)
    buf[*loc + i] = ' ';
  i = *loc;
  *loc = i + count;
  return i;
}
