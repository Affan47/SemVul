history_truncate_file (fname, lines)
     const char *fname;
     int lines;
{
  char *buffer, *filename, *bp, *bp1;
  int file, chars_read, rv;
  struct stat finfo;
  size_t file_size;

  buffer = (char *)NULL;
  filename = history_filename (fname);
  file = open (filename, O_RDONLY|O_BINARY, 0666);
  rv = 0;


  if (file == -1 || fstat (file, &finfo) == -1)
    {
      rv = errno;
      if (file != -1)
	close (file);
      goto truncate_exit;
    }

  if (S_ISREG (finfo.st_mode) == 0)
    {
      close (file);
#ifdef EFTYPE
      rv = EFTYPE;
#else
      rv = EINVAL;
#endif
      goto truncate_exit;
    }

  file_size = (size_t)finfo.st_size;


  if (file_size != finfo.st_size || file_size + 1 < file_size)
    {
      close (file);
#if defined (EFBIG)
      rv = errno = EFBIG;
#elif defined (EOVERFLOW)
      rv = errno = EOVERFLOW;
#else
      rv = errno = EINVAL;
#endif
      goto truncate_exit;
    }

  buffer = (char *)malloc (file_size + 1);
  if (buffer == 0)
    {
      close (file);
      goto truncate_exit;
    }

  chars_read = read (file, buffer, file_size);
  close (file);

  if (chars_read <= 0)
    {
      rv = (chars_read < 0) ? errno : 0;
      goto truncate_exit;
    }


  for (bp1 = bp = buffer + chars_read - 1; lines && bp > buffer; bp--)
    {
      if (*bp == '\n' && HIST_TIMESTAMP_START(bp1) == 0)
	lines--;
      bp1 = bp;
    }


  for ( ; bp > buffer; bp--)
    {
      if (*bp == '\n' && HIST_TIMESTAMP_START(bp1) == 0)
        {
	  bp++;
	  break;
        }
      bp1 = bp;
    }


  if (bp > buffer && ((file = open (filename, O_WRONLY|O_TRUNC|O_BINARY, 0600)) != -1))
    {
      write (file, bp, chars_read - (bp - buffer));

#if defined (__BEOS__)

      ftruncate (file, chars_read - (bp - buffer));
#endif

      close (file);
    }

 truncate_exit:

  FREE (buffer);

  free (filename);
  return rv;
}
