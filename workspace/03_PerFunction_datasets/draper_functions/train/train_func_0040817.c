cupsTempFile2(char *filename,
              int  len)
{
  cups_file_t	*file;
  int		fd;


  if ((fd = cupsTempFd(filename, len)) < 0)
    return (NULL);
  else if ((file = cupsFileOpenFd(fd, "w")) == NULL)
  {
    close(fd);
    unlink(filename);
    return (NULL);
  }
  else
    return (file);
}
