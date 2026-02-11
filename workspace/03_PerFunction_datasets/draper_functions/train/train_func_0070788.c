gt_cntlist_show(GtBitsequence *cntlist, unsigned long nofreads,
    const char *path, bool binary, GtError *err)
{
  FILE *file;
  gt_assert(cntlist != NULL);
  if (path == NULL)
    file = stdout;
  else
  {
    file = gt_fa_fopen(path, binary ? "wb" : "w", err);
    if (file == NULL)
      return -1;
  }
  gt_assert(file != NULL);
  (binary ? gt_cntlist_show_bit : gt_cntlist_show_ascii)
    (cntlist, nofreads, file);
  if (path != NULL)
    gt_fa_fclose(file);
  return 0;
}
