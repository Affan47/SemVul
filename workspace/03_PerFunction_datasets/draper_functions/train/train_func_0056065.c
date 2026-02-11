fos_readdir (const char *path, void *buf, fuse_fill_dir_t filler,
             off_t offset, struct fuse_file_info *fi)
{
  int ret = -ENOENT;
  char *location;
  fosfat_file_t *files, *first_file;

  (void) offset;
  (void) fi;

  location = trim_fosname (path);


  filler (buf, "..", NULL, 0);


  files = fosfat_list_dir (fosfat, location);
  if (!files)
    goto out;

  first_file = files;

  do
  {
    char _path[256];
    struct stat *st;
    char *name;

    snprintf (_path, sizeof (_path), "%s/%s", location, files->name);
    st = in_stat (files, _path);


    if (g_pbm && strstr (files->name, ".image\0")
        && fosgra_is_image (fosfat, _path))
    {
      name = calloc (1, strlen (files->name) + strlen (FOSGRAID) + 6);
      sprintf (name, "%s." FOSGRAID ".pbm", files->name);
    }

    else if (g_xpm && strstr (files->name, ".color\0")
             && fosgra_is_image (fosfat, _path))
    {
      name = calloc (1, strlen (files->name) + strlen (FOSGRAID) + 6);
      sprintf (name, "%s." FOSGRAID ".xpm", files->name);
    }
    else
      name = strdup (files->name);

    if (strstr (name, ".dir"))
      *(name + strlen (name) - 4) = '\0';


    filler (buf, name, st, 0);
    free (st);
    free (name);
  }
  while ((files = files->next_file));

  fosfat_free_listdir (first_file);
  ret = 0;

 out:
  if (location)
    free (location);

  return ret;
}
