hdf_init (HDF **hdf)
{
  NEOERR *err;
  HDF *my_hdf;

  *hdf = NULL;

  err = nerr_init();
  if (err != STATUS_OK)
    return nerr_pass (err);

  err = _alloc_hdf (&my_hdf, NULL, 0, NULL, 0, 0, NULL);
  if (err != STATUS_OK)
    return nerr_pass (err);

  my_hdf->top = my_hdf;

  *hdf = my_hdf;

  return STATUS_OK;
}
