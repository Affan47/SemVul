read_wcstr(const int discard)
{
  gbint16* buff = NULL, c;
  int size = 0, pos = 0;

  while (gbfread(&c, sizeof(c), 1, fin) && (c != 0)) {
    if (size == 0) {
      size = 16;
      buff = (gbint16*) xmalloc(size * sizeof(*buff));
    } else if (pos == size) {
      size += 16;
      buff = (gbint16*) xrealloc(buff, size * sizeof(*buff));
    }
    buff[pos] = c;
    pos += 1;
  }

  if (pos != 0) {
    char* res;
    if (discard) {
      res = NULL;
    } else {
      res = cet_str_uni_to_utf8(buff, pos);
      res = lrtrim(res);
      if (*res == '\0') {
        xfree(res);
        res = NULL;
      }
    }
    xfree(buff);
    return res;
  } else {
    return NULL;
  }
}
