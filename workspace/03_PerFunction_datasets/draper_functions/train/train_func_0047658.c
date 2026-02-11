fgets_jconf(char *buf, int size, FILE *fp)
{
  int c, prev_c;
  int pos;

  if (fp == NULL) return NULL;

  pos = 0;
  c = '\0';
  prev_c = '\0';
  while (1) {
    if (pos >= size) {
      pos--;
      break;
    }

    c = fgetc(fp);
    if (c == EOF) {
      buf[pos] = '\0';
      if (pos <= 0) {
	return NULL;
      } else {
	return buf;
      }
    } else if (c == '\n' || c == '\r') {
      if (c == '\r' && (c = fgetc(fp)) != '\n') {
	ungetc(c, fp);
      }
      if (prev_c == '\\') {
	pos--;
      } else {
	break;
      }
    } else {
      buf[pos] = c;
      pos++;

#if defined(_WIN32) && !defined(__CYGWIN32__)
      if (c == '\\' && (_ismbblead(prev_c) && _ismbbtrail(c))) {
      c = '\0';
      }
#endif
    }
    prev_c = c;
  }
  buf[pos] = '\0';

  return buf;
}
