here_document_to_fd (redirectee, ri)
     WORD_DESC *redirectee;
     enum r_instruction ri;
{
  char *filename;
  int r, fd, fd2;

  fd = sh_mktmpfd ("sh-thd", MT_USERANDOM|MT_USETMPDIR, &filename);


  if (fd < 0)
    {
      FREE (filename);
      return (fd);
    }

  errno = r = 0;

  if (redirectee->word)
    r = (ri != r_reading_string) ? write_here_document (fd, redirectee)
				 : write_here_string (fd, redirectee);

  if (r)
    {
      close (fd);
      unlink (filename);
      free (filename);
      errno = r;
      return (-1);
    }


  fd2 = open (filename, O_RDONLY, 0600);

  if (fd2 < 0)
    {
      r = errno;
      unlink (filename);
      free (filename);
      close (fd);
      errno = r;
      return -1;
    }

  close (fd);
  if (unlink (filename) < 0)
    {
      r = errno;
#if defined (__CYGWIN__)


      if (r == EACCES)
	return (fd2);
#endif
      close (fd2);
      free (filename);
      errno = r;
      return (-1);
    }

  free (filename);
  return (fd2);
}
