cdk_keydb_new_from_file (cdk_keydb_hd_t * r_hd, int secret, const char *fname)
{
  cdk_keydb_hd_t hd;

  if (!r_hd)
    {
      gnutls_assert ();
      return CDK_Inv_Value;
    }
  *r_hd = NULL;
  hd = calloc (1, sizeof *hd);
  hd->name = cdk_strdup (fname);
  if (!hd->name)
    {
      cdk_free (hd);
      gnutls_assert ();
      return CDK_Out_Of_Core;
    }
  hd->type = secret ? CDK_DBTYPE_SK_KEYRING : CDK_DBTYPE_PK_KEYRING;
  hd->secret = secret;
  *r_hd = hd;
  return 0;
}
