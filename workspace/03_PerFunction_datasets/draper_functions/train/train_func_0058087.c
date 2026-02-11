he_search(hedit, exp, replace, direction, wrap, increment, end,
          replace_str, replace_len, match_len)
  struct he_s *hedit;
  char *exp;


  char *replace;


  int direction;


  int wrap;


  int increment;


  long end;


  char **replace_str;


  long *replace_len;


  long *match_len;


{
  static long *regex;
  long position;


  regex_init(rxwrap_read, rxwrap_seek, rxwrap_tell);
  rxwrap_current_buffer = hedit->buffer;
  regex_reset();

  if (wrap || end < 0) end = hedit->buffer->size;

  if (exp) if (!(regex = regex_compile(exp, replace))) return -2;
  if (direction < 0) direction = -1; else direction = 1;
  if (direction > 0) {
    position = regex_search(regex, 0, end, hedit->position + !!increment,
                            1, replace_str, replace_len, match_len);
    if (wrap && position < 0) {
      position = regex_search(regex, 0, end, 0, 1,
                              replace_str, replace_len, match_len);
      if (position >= 0) he_message(0, "@Abwrapped@~");
    }
  } else {
    position = regex_search(regex, 0, end, hedit->position - !!hedit->position,
                            -1, replace_str, replace_len, match_len);
    if (wrap && position < 0) {
      position = regex_search(regex, 0, end, hedit->buffer->size - 1,
                              -1, replace_str, replace_len, match_len);
      if (position >= 0) he_message(0, "@Abwrapped@~");
    }
  }
  return position;
}
