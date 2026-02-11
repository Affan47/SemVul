gnutls_openpgp_get_key (gnutls_datum_t * key,
                        gnutls_openpgp_keyring_t keyring, key_attr_t by,
                        opaque * pattern)
{
  cdk_kbnode_t knode = NULL;
  unsigned long keyid[2];
  unsigned char *buf;
  void *desc;
  size_t len;
  int rc = 0;
  cdk_keydb_search_t st;

  if (!key || !keyring || by == KEY_ATTR_NONE)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  memset (key, 0, sizeof *key);

  if (by == KEY_ATTR_SHORT_KEYID)
    {
      keyid[0] = _gnutls_read_uint32 (pattern);
      desc = keyid;
    }
  else if (by == KEY_ATTR_KEYID)
    {
      keyid[0] = _gnutls_read_uint32 (pattern);
      keyid[1] = _gnutls_read_uint32 (pattern + 4);
      desc = keyid;
    }
  else
    desc = pattern;
  rc = cdk_keydb_search_start (&st, keyring->db, by, desc);
  if (!rc)
    rc = cdk_keydb_search (st, keyring->db, &knode);

  cdk_keydb_search_release (st);

  if (rc)
    {
      rc = _gnutls_map_cdk_rc (rc);
      goto leave;
    }

  if (!cdk_kbnode_find (knode, CDK_PKT_PUBLIC_KEY))
    {
      rc = GNUTLS_E_OPENPGP_GETKEY_FAILED;
      goto leave;
    }


  rc = cdk_kbnode_write_to_mem_alloc (knode, &buf, &len);
  if (!rc)
    datum_append (key, buf, len);
  gnutls_free (buf);

leave:
  cdk_kbnode_release (knode);
  return rc;
}
