fold_file (char const *filename, size_t width)
{
  FILE *istream;
  int c;
  size_t column = 0;
  size_t offset_out = 0;
  static char *line_out = NULL;
  static size_t allocated_out = 0;
  int saved_errno;

  if (STREQ (filename, "-"))
    {
      istream = stdin;
      have_read_stdin = true;
    }
  else
    istream = fopen (filename, "r");

  if (istream == NULL)
    {
      error (0, errno, "%s", filename);
      return false;
    }

  fadvise (istream, FADVISE_SEQUENTIAL);

  while ((c = getc (istream)) != EOF)
    {
      if (offset_out + 1 >= allocated_out)
        line_out = X2REALLOC (line_out, &allocated_out);

      if (c == '\n')
        {
          line_out[offset_out++] = c;
          fwrite (line_out, sizeof (char), offset_out, stdout);
          column = offset_out = 0;
          continue;
        }

    rescan:
      column = adjust_column (column, c);

      if (column > width)
        {


          if (break_spaces)
            {
              bool found_blank = false;
              size_t logical_end = offset_out;


              while (logical_end)
                {
                  --logical_end;
                  if (isblank (to_uchar (line_out[logical_end])))
                    {
                      found_blank = true;
                      break;
                    }
                }

              if (found_blank)
                {
                  size_t i;


                  logical_end++;
                  fwrite (line_out, sizeof (char), (size_t) logical_end,
                          stdout);
                  putchar ('\n');


                  memmove (line_out, line_out + logical_end,
                           offset_out - logical_end);
                  offset_out -= logical_end;
                  for (column = i = 0; i < offset_out; i++)
                    column = adjust_column (column, line_out[i]);
                  goto rescan;
                }
            }

          if (offset_out == 0)
            {
              line_out[offset_out++] = c;
              continue;
            }

          line_out[offset_out++] = '\n';
          fwrite (line_out, sizeof (char), (size_t) offset_out, stdout);
          column = offset_out = 0;
          goto rescan;
        }

      line_out[offset_out++] = c;
    }

  saved_errno = errno;

  if (offset_out)
    fwrite (line_out, sizeof (char), (size_t) offset_out, stdout);

  if (ferror (istream))
    {
      error (0, saved_errno, "%s", filename);
      if (!STREQ (filename, "-"))
        fclose (istream);
      return false;
    }
  if (!STREQ (filename, "-") && fclose (istream) == EOF)
    {
      error (0, errno, "%s", filename);
      return false;
    }

  return true;
}
