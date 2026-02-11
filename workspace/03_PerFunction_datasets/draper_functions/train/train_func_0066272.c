make_link(const char *dst,
          const char *src)
{
  char	buffer[8192],
	*slash;


  strcpy(buffer, dst);
  if ((slash = strrchr(buffer, '/')) != NULL)
    *slash = '\0';

  if (access(buffer, F_OK))
    make_directory(buffer, 0755, 0, 0);


  return (symlink(src, dst));
}
