_dbx_info_cmp(const dbx_info_t *ia, const dbx_info_t *ib)
{
  int res = strcmp(ia->filename, ib->filename);
  if (res == 0) {
    res = ia->index - ib->index;
  }
  return res;
}
