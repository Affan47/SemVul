aix_addfile(int        type,
            const char *src,
            const char *dst,
	    int        num_dirs,
            aixdir_t   **dirs)
{
  int		i, j;
  int		blocks;
  struct stat	fileinfo;
  aixdir_t	*temp;
  char		dstpath[1024],
		*dstptr;


  strlcpy(dstpath, dst, sizeof(dstpath));

  if (type == 'd')
  {
    blocks = 1;
    dstptr = dstpath + strlen(dstpath) - 1;
  }
  else
  {
    dstptr = strrchr(dstpath, '/');

    if (type == 'l')
      blocks = 1;
    else if (!stat(src, &fileinfo))
      blocks = (fileinfo.st_size + 511) / 512;
    else
      blocks = 0;
  }

  if (dstptr && *dstptr == '/' && dstptr > dstpath)
    *dstptr = '\0';


  temp = *dirs;

  for (i = 0; i < num_dirs; i ++)
    if ((j = strcmp(temp[i].dst, dstpath)) == 0)
    {
      temp[i].blocks += blocks;
      return (num_dirs);
    }
    else if (j > 0)
      break;


  if (num_dirs == 0)
    temp = malloc(sizeof(aixdir_t));
  else
    temp = realloc(*dirs, (num_dirs + 1) * sizeof(aixdir_t));

  if (!temp)
    return (num_dirs);

  *dirs = temp;
  temp  += i;

  if (i < num_dirs)
    memmove(temp + 1, temp, (num_dirs - i) * sizeof(aixdir_t));

  strcpy(temp->dst, dstpath);
  temp->blocks = blocks;

  return (num_dirs + 1);
}
