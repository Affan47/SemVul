writefmdata(const char *indexname,
                       Fmindex *fm,
                       bool storeindexpos,
                       GtError *err)
{
  FILE *fp;

  gt_error_check(err);
  fp = gt_fa_fopen_with_suffix(indexname,FMDATAFILESUFFIX,"wb",err);
  if (fp == NULL)
  {
    return -1;
  }
  if (gt_flushfmindex2file(fp,fm,storeindexpos,err) != 0)
  {
    return -2;
  }
  gt_fa_xfclose(fp);
  return 0;
}
