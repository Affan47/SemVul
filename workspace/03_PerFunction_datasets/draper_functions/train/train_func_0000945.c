_getRequiredSize(struct SFNTContainer *ctr)
{
  unsigned ret = 12;
  ret += _getTableDirectorySize(ctr);
  for (unsigned i = 0; i < ctr->numTables; ++i)
  {
    struct SFNTTable *tbl = &ctr->tables[i];
    ret += ((tbl->bufSize + 3) / 4) * 4;
  }
  return ret;
}
