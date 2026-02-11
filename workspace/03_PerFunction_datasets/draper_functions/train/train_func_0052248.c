_cdk_pkt_detach_free (cdk_packet_t pkt, int *r_pkttype, void **ctx)
{

  switch (pkt->pkttype)
    {
    case CDK_PKT_PUBLIC_KEY:
    case CDK_PKT_PUBLIC_SUBKEY:
      *ctx = pkt->pkt.public_key;
      break;

    case CDK_PKT_SECRET_KEY:
    case CDK_PKT_SECRET_SUBKEY:
      *ctx = pkt->pkt.secret_key;
      break;

    default:
      *r_pkttype = 0;
      return;
    }


  if (r_pkttype)
    *r_pkttype = pkt->pkttype;

  cdk_free (pkt);
}
