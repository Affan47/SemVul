ppdb_rd_deinit(void)
{
  pdb_close(file_in);
  str_pool_deinit();
  if (datefmt) {
    xfree(datefmt);
  }
}
