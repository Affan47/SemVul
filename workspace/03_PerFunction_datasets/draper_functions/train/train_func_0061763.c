linkat_follow (int fd1, char const *file1, int fd2, char const *file2)
{
  char *name = (char *) file1;
  char *target;
  int result;
  int i = MAXSYMLINKS;


  while (i-- && (target = areadlinkat (fd1, name)))
    {
      if (IS_ABSOLUTE_FILE_NAME (target))
        {
          if (name != file1)
            free (name);
          name = target;
        }
      else
        {
          char *dir = mdir_name (name);
          if (name != file1)
            free (name);
          if (!dir)
            {
              free (target);
              errno = ENOMEM;
              return -1;
            }
          name = mfile_name_concat (dir, target, NULL);
          free (dir);
          free (target);
          if (!name)
            {
              errno = ENOMEM;
              return -1;
            }
        }
    }
  if (i < 0)
    {
      target = NULL;
      errno = ELOOP;
    }
  if (!target && errno != EINVAL)
    {
      if (name != file1)
        {
          int saved_errno = errno;
          free (name);
          errno = saved_errno;
        }
      return -1;
    }
  result = linkat (fd1, name, fd2, file2, 0);
  if (name != file1)
    {
      int saved_errno = errno;
      free (name);
      errno = saved_errno;
    }
  return result;
}
