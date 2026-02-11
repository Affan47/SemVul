cdk_keydb_idx_rebuild (cdk_keydb_hd_t db, cdk_keydb_search_t dbs)
{
  struct stat stbuf;
  char *tmp_idx_name;
  cdk_error_t rc;
  int err;

  if (!db || !db->name || !dbs)
    {
      gnutls_assert ();
      return CDK_Inv_Value;
    }
  if (db->secret)
    return 0;

  tmp_idx_name = keydb_idx_mkname (db->name);
  if (!tmp_idx_name)
    {
      gnutls_assert ();
      return CDK_Out_Of_Core;
    }
  err = stat (tmp_idx_name, &stbuf);
  cdk_free (tmp_idx_name);


  if (err)
    return 0;

  cdk_stream_close (dbs->idx);
  dbs->idx = NULL;
  if (!dbs->idx_name)
    {
      dbs->idx_name = keydb_idx_mkname (db->name);
      if (!dbs->idx_name)
        {
          gnutls_assert ();
          return CDK_Out_Of_Core;
        }
    }
  rc = keydb_idx_build (db->name);
  if (!rc)
    rc = cdk_stream_open (dbs->idx_name, &dbs->idx);
  else
    gnutls_assert ();
  return rc;
}
