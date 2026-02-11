gnutls_openpgp_privkey_get_revoked_status (gnutls_openpgp_privkey_t key)
{
  cdk_packet_t pkt;

  if (!key)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  pkt = cdk_kbnode_find_packet (key->knode, CDK_PKT_SECRET_KEY);
  if (!pkt)
    return GNUTLS_E_OPENPGP_GETKEY_FAILED;

  if (pkt->pkt.secret_key->is_revoked != 0)
    return 1;
  return 0;
}
