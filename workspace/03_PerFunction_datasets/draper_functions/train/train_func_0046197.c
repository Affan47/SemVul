parseref(Logfile *lf, void *arg, char c) {


  register char *p = pos;
  Memman *m = (Memman *)arg;
  size_t length = 0;

  char *string_start;
  string_start = p;

  *block_end = '\r';
  termchar[(unsigned char)c] = TRUE;


  while (!termchar[(unsigned char)(*p)] ||
	 (*p == c && (*(p + 1) != '-' || *(p + 2) != '>'))) {
    p++;
    length++;
  }

  if (p == block_end) {
    if (record_start == block_start) {
      if (c != '\r' && c != '\n' && c != '\0')
	termchar[(unsigned char)c] = FALSE;
      pos = p;
      return(FALSE);
    }
    string_start -= record_start - block_start;
    pos = p;
    shunt_data(lf);
    p = pos;
    *block_end = '\r';
    while (!termchar[(unsigned char)(*p)] ||
	   (*p == c && (*(p + 1) != '-' || *(p + 2) != '>'))) {
      p++;
      length++;
    }
    if (p == block_end) {
      if (c != '\r' && c != '\n' && c != '\0')
	termchar[(unsigned char)c] = FALSE;
      pos = p;
      return(FALSE);
    }
  }

  if (c != '\r' && c != '\n' && c != '\0')
    termchar[(unsigned char)c] = FALSE;
  if (*p != c) {
    pos = p;
    return(FALSE);
  }

  memcpy(submalloc(m, length + 1), (void *)string_start, length);
  *((char *)(m->next_pos) - 1) = '\0';
  p++;

  pos = p;
  return(TRUE);
}
