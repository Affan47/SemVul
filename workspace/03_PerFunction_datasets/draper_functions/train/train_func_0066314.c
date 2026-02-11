pw_free_path (char ** path)
{
  int i;
  if (path)
    for (i = 0 ; path[i] ; i++)
      free (path[i]);
  XFREE (path);
}
