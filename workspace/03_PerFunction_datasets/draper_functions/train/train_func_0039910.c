extract_escapes(const char *format, char *escapes,
                              size_t max_escapes)
{
  static const char format_escapes[] = {
    '*', 'd', 'i', 'o', 'u', 'x', 'X', 'e', 'E', 'f',
    'F', 'g', 'G', 'a', 'A', 'c', 's', 'p', 'n',
  };
  bool reordered = FALSE;
  size_t num = 0;
  int index = 0;

  memset(escapes, 0, max_escapes);
  format = strchr(format, '%');
  while (NULL != format) {
    format++;
    if ('%' == *format) {

      continue;
    } else if (fc_isdigit(*format)) {
      const char *start = format;

      do {
        format++;
      } while (fc_isdigit(*format));
      if ('$' == *format) {

        sscanf(start, "%d", &index);
        reordered = TRUE;
      }
    }

    while ('\0' != *format
           && NULL == strchr(format_escapes, *format)) {
      format++;
    }
    escapes[index] = *format;


    if (reordered) {
      if (index > num) {
        num = index;
      }
    } else {
      index++;
      num++;
    }

    if ('*' != *format) {
      format = strchr(format, '%');
    }
  }
  return num;
}
