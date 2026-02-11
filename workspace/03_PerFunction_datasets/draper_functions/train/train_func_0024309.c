sh_xmalloc (bytes, file, line)
     size_t bytes;
     char *file;
     int line;
{
  PTR_T temp;

#if defined (DEBUG)
  if (bytes == 0)
    internal_warning("xmalloc: %s:%d: size argument is 0", file, line);
#endif

  FINDBRK();
  temp = sh_malloc (bytes, file, line);

  if (temp == 0)
    sh_allocerr ("xmalloc", bytes, file, line);

  return (temp);
}
