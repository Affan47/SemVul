cddb_mc_write_disc_data(int cd_desc, struct disc_mc_data *data)
{
  struct disc_data *outdata;

  if((outdata = malloc(sizeof(struct disc_data))) == NULL)
    return -1;

  if(cddb_data_copy_from_mc(outdata, data) < 0) {
    free(outdata);
    return -1;
  }

  if(cddb_write_data(cd_desc, outdata) < 0) {
    free(outdata);
    return -1;
  }

  free(outdata);
  return 0;
}
