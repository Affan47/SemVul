AcquireTemporaryFileStream(char *filename,
  FileIOMode mode)
{
  int
    fd;

  if ((fd=AcquireTemporaryFileDescriptor(filename)) != -1)
    {
      if (mode == TextFileIOMode)
        return fdopen(fd,"w+");
      return fdopen(fd,"wb+");
    }

  return (FILE *) NULL;
}
