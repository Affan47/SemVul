gnutls_openpgp_count_key_names (const gnutls_datum_t * cert)
{
  cdk_kbnode_t knode, p, ctx;
  cdk_packet_t pkt;
  int nuids;

  if (cert == NULL)
    {
      gnutls_assert ();
      return 0;
    }

  if (cdk_kbnode_read_from_mem (&knode, cert->data, cert->size))
    {
      gnutls_assert ();
      return 0;
    }

  ctx = NULL;
  for (nuids = 0;;)
    {
      p = cdk_kbnode_walk (knode, &ctx, 0);
      if (!p)
        break;
      pkt = cdk_kbnode_get_packet (p);
      if (pkt->pkttype == CDK_PKT_USER_ID)
        nuids++;
    }

  cdk_kbnode_release (knode);
  return nuids;
}
