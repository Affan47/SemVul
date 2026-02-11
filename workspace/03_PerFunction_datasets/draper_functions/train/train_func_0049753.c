skip (uintmax_t n_skip)
{
  bool ok = true;
  int in_errno = 0;

  if (n_skip == 0)
    return true;

  while (in_stream != NULL)
    {
      struct stat file_stats;


      if (fstat (fileno (in_stream), &file_stats) == 0)
        {


          if (S_ISREG (file_stats.st_mode) && 0 < file_stats.st_size)
            {
              if ((uintmax_t) file_stats.st_size < n_skip)
                n_skip -= file_stats.st_size;
              else
                {
                  if (fseeko (in_stream, n_skip, SEEK_CUR) != 0)
                    {
                      in_errno = errno;
                      ok = false;
                    }
                  n_skip = 0;
                }
            }


          else
            {
              char buf[BUFSIZ];
              size_t n_bytes_read, n_bytes_to_read = BUFSIZ;

              while (0 < n_skip)
                {
                  if (n_skip < n_bytes_to_read)
                    n_bytes_to_read = n_skip;
                  n_bytes_read = fread (buf, 1, n_bytes_to_read, in_stream);
                  n_skip -= n_bytes_read;
                  if (n_bytes_read != n_bytes_to_read)
                    {
                      in_errno = errno;
                      ok = false;
                      n_skip = 0;
                      break;
                    }
                }
            }

          if (n_skip == 0)
            break;
        }

      else
        {
          error (0, errno, "%s", input_filename);
          ok = false;
        }

      ok &= check_and_close (in_errno);

      ok &= open_next_file ();
    }

  if (n_skip != 0)
    error (EXIT_FAILURE, 0, _("cannot skip past end of combined input"));

  return ok;
}
