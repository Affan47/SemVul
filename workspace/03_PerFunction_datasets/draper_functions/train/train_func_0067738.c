get_dword(struct hive *hdesc, int vofs, char *path, int exact)
{
  struct keyval *v;
  int dword;

  v = get_val2buf(hdesc, NULL, vofs, path, REG_DWORD, exact | TPF_VK);
  if (!v) return(-1);

  dword = (int)v->data;

  FREE(v);

  return(dword);

}
