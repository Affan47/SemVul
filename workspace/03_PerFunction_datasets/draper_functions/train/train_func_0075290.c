bgav_http_header_add_line(bgav_http_header_t * h, const char * line)
  {
  int len;
  if(h->lines_alloc < h->num_lines + 1)
    {
    h->lines_alloc += 8;
    h->lines = realloc(h->lines, h->lines_alloc * sizeof(*(h->lines)));
    memset(h->lines + h->num_lines, 0,
           (h->lines_alloc - h->num_lines) * sizeof(*(h->lines)));
    }
  len = strlen(line)+1;
  if(h->lines[h->num_lines].line_alloc < len)
    {
    h->lines[h->num_lines].line_alloc = len + 100;
    h->lines[h->num_lines].line =
      realloc(h->lines[h->num_lines].line,
              h->lines[h->num_lines].line_alloc);
    }
  strcpy(h->lines[h->num_lines].line, line);
  h->num_lines++;
  }
