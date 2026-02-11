keydb_pos_from_cache (cdk_keydb_hd_t hd, cdk_keydb_search_t ks,
                      int *r_cache_hit, off_t * r_off)
{
  key_table_t c;

  if (!hd || !r_cache_hit || !r_off)
    {
      gnutls_assert ();
      return CDK_Inv_Value;
    }


  *r_cache_hit = 0;
  *r_off = 0;

  c = keydb_cache_find (ks);
  if (c != NULL)
    {
      _cdk_log_debug ("cache: found entry in cache.\n");
      *r_cache_hit = 1;
      *r_off = c->offset;
      return 0;
    }


  if (!ks->idx)
    return 0;

  if (ks->idx)
    {
      if (ks->type == CDK_DBSEARCH_KEYID)
        {
          if (keydb_idx_search (ks->idx, ks->u.keyid, NULL, r_off))
            {
              gnutls_assert ();
              return CDK_Error_No_Key;
            }
          _cdk_log_debug ("cache: found keyid entry in idx table.\n");
          *r_cache_hit = 1;
        }
      else if (ks->type == CDK_DBSEARCH_FPR)
        {
          if (keydb_idx_search (ks->idx, NULL, ks->u.fpr, r_off))
            {
              gnutls_assert ();
              return CDK_Error_No_Key;
            }
          _cdk_log_debug ("cache: found fpr entry in idx table.\n");
          *r_cache_hit = 1;
        }
    }

  return 0;
}
