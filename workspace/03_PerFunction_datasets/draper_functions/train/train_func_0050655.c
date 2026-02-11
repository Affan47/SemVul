get_file_parts(ext2_filsys fs, ext2_ino_t root, char *pathname,
               ext2_ino_t *dir_ino, char **dir_name, char **base_name)
{
  char *fname;
  long retval;


  *dir_name = pathname;
  *dir_ino = root;
  if (NULL == (fname = strrchr(pathname, '/')))
    {
      fname = pathname;
      *dir_name = NULL;
    }
  else
    {
      *fname++ = '\0';
      if ((*pathname != '\0' && strcmp(pathname, ".") != 0) &&
          (retval = change_cwd(fs, root, dir_ino, pathname)))
        {
          fprintf(stderr, "Error changing to directory %s\n",
                  pathname);
          return(retval);
        }
    }

    *base_name = fname;
    return(0);
}
