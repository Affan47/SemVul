ppdb_wr_deinit(void)
{
  mkshort_del_handle(&mkshort_handle);
  pdb_close(file_out);
  str_pool_deinit();
  xfree(fname_out);
  if (datefmt) {
    xfree(datefmt);
  }
  if (appinfo) {
    xfree(appinfo);
  }
}
