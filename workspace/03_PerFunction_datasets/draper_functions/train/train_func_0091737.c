fl_filename_free_list(struct dirent ***list, int n)
{
  if (n<0) return;

  int i;
  for (i = 0; i < n; i ++) {
    if ((*list)[i])
      free((*list)[i]);
  }
  free(*list);
  *list = 0;
}
