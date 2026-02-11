add_exclude_file (void (*add_func) (struct exclude *, char const *, int),
                  struct exclude *ex, char const *file_name, int options,
                  char line_end)
{
  bool use_stdin = file_name[0] == '-' && !file_name[1];
  FILE *in;
  char *buf = NULL;
  char *p;
  char const *pattern;
  char const *lim;
  size_t buf_alloc = 0;
  size_t buf_count = 0;
  int c;
  int e = 0;

  if (use_stdin)
    in = stdin;
  else if (! (in = fopen (file_name, "r")))
    return -1;

  while ((c = getc (in)) != EOF)
    {
      if (buf_count == buf_alloc)
        buf = x2realloc (buf, &buf_alloc);
      buf[buf_count++] = c;
    }

  if (ferror (in))
    e = errno;

  if (!use_stdin && fclose (in) != 0)
    e = errno;

  buf = xrealloc (buf, buf_count + 1);
  buf[buf_count] = line_end;
  lim = buf + buf_count + ! (buf_count == 0 || buf[buf_count - 1] == line_end);
  pattern = buf;

  for (p = buf; p < lim; p++)
    if (*p == line_end)
      {
        char *pattern_end = p;

        if (isspace ((unsigned char) line_end))
          {
            for (; ; pattern_end--)
              if (pattern_end == pattern)
                goto next_pattern;
              else if (! isspace ((unsigned char) pattern_end[-1]))
                break;
          }

        *pattern_end = '\0';
        (*add_func) (ex, pattern, options);

      next_pattern:
        pattern = p + 1;
      }

  errno = e;
  return e ? -1 : 0;
}
