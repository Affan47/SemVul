find_in_path_element (name, path, flags, name_len, dotinfop)
     const char *name;
     char *path;
     int flags, name_len;
     struct stat *dotinfop;
{
  int status;
  char *full_path, *xpath;

  xpath = (*path == '~') ? bash_tilde_expand (path, 0) : path;


  if (dot_found_in_search == 0 && *xpath == '.')
    dot_found_in_search = same_file (".", xpath, dotinfop, (struct stat *)NULL);

  full_path = sh_makepath (xpath, name, 0);

  status = file_status (full_path);

  if (xpath != path)
    free (xpath);

  if ((status & FS_EXISTS) == 0)
    {
      free (full_path);
      return ((char *)NULL);
    }


  if (flags & FS_EXISTS)
    return (full_path);


  if ((flags & FS_READABLE) && (status & FS_READABLE))
    return (full_path);


  if ((status & FS_EXECABLE) && (flags & (FS_EXEC_ONLY|FS_EXEC_PREFERRED)) &&
      (((flags & FS_NODIRS) == 0) || ((status & FS_DIRECTORY) == 0)))
    {
      FREE (file_to_lose_on);
      file_to_lose_on = (char *)NULL;
      return (full_path);
    }


  if ((flags & FS_EXEC_PREFERRED) && file_to_lose_on == 0)
    file_to_lose_on = savestring (full_path);


  if ((flags & (FS_EXEC_ONLY|FS_EXEC_PREFERRED)) ||
      ((flags & FS_NODIRS) && (status & FS_DIRECTORY)) ||
      ((flags & FS_READABLE) && (status & FS_READABLE) == 0))
    {
      free (full_path);
      return ((char *)NULL);
    }
  else
    return (full_path);
}
