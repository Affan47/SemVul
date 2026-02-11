isakmp_next_payload(packet_t * pkt, u_int8_t next)
{
  switch (next)
    {
    case ISAKMP_PAYLOAD_DELETE:
      dump_isakmp_delete(pkt);
      break;

    case ISAKMP_PAYLOAD_SA:
      dump_isakmp_sa(pkt);
      break;

    case ISAKMP_PAYLOAD_VENDORID:
      dump_isakmp_vendorid(pkt);
      break;

    default:

      break;
    }
}
