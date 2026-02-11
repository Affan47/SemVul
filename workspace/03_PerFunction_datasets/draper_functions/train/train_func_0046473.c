file_lines (const char *pretty_filename, int fd, uintmax_t n_lines,
            off_t start_pos, off_t end_pos, uintmax_t *read_pos)
{
  char buffer[BUFSIZ];
  size_t bytes_read;
  off_t pos = end_pos;

  if (n_lines == 0)
    return true;


  bytes_read = (pos - start_pos) % BUFSIZ;
  if (bytes_read == 0)
    bytes_read = BUFSIZ;


  pos -= bytes_read;
  xlseek (fd, pos, SEEK_SET, pretty_filename);
  bytes_read = safe_read (fd, buffer, bytes_read);
  if (bytes_read == SAFE_READ_ERROR)
    {
      error (0, errno, _("error reading %s"), quote (pretty_filename));
      return false;
    }
  *read_pos = pos + bytes_read;


  if (bytes_read && buffer[bytes_read - 1] != '\n')
    --n_lines;

  do
    {


      size_t n = bytes_read;
      while (n)
        {
          char const *nl;
          nl = memrchr (buffer, '\n', n);
          if (nl == NULL)
            break;
          n = nl - buffer;
          if (n_lines-- == 0)
            {


              if (n != bytes_read - 1)
                xwrite_stdout (nl + 1, bytes_read - (n + 1));
              *read_pos += dump_remainder (pretty_filename, fd,
                                           end_pos - (pos + bytes_read));
              return true;
            }
        }


      if (pos == start_pos)
        {


          xlseek (fd, start_pos, SEEK_SET, pretty_filename);
          *read_pos = start_pos + dump_remainder (pretty_filename, fd,
                                                  end_pos);
          return true;
        }
      pos -= BUFSIZ;
      xlseek (fd, pos, SEEK_SET, pretty_filename);

      bytes_read = safe_read (fd, buffer, BUFSIZ);
      if (bytes_read == SAFE_READ_ERROR)
        {
          error (0, errno, _("error reading %s"), quote (pretty_filename));
          return false;
        }

      *read_pos = pos + bytes_read;
    }
  while (bytes_read > 0);

  return true;
}
