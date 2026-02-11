gnutls_openpgp_keyring_check_id (gnutls_openpgp_keyring_t ring,
                                 const gnutls_openpgp_keyid_t keyid,
                                 unsigned int flags)
{
  cdk_pkt_pubkey_t pk;
  uint32_t id[2];

  id[0] = _gnutls_read_uint32 (keyid);
  id[1] = _gnutls_read_uint32 (&keyid[4]);

  if (!cdk_keydb_get_pk (ring->db, id, &pk))
    {
      cdk_pk_release (pk);
      return 0;
    }

  _gnutls_debug_log ("PGP: key not found %08lX\n", (unsigned long) id[1]);
  return GNUTLS_E_NO_CERTIFICATE_FOUND;
}
