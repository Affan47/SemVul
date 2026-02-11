free_dir (struct s_file *files)
{
  struct s_file *fp;

  for (fp=files; fp; fp=fp->next) {
    if (fp->name)
      free (fp->name);
    free (fp);
  }
}
