_get_secret_subkey (gnutls_openpgp_privkey_t key, unsigned int indx)
{
  cdk_kbnode_t p, ctx;
  cdk_packet_t pkt;
  unsigned int subkeys;

  ctx = NULL;
  subkeys = 0;
  while ((p = cdk_kbnode_walk (key->knode, &ctx, 0)))
    {
      pkt = cdk_kbnode_get_packet (p);
      if (pkt->pkttype == CDK_PKT_SECRET_SUBKEY && indx == subkeys++)
        return pkt;
    }

  return NULL;
}
