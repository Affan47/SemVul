dump_payload(packet_t *pkt)
{
  char   holder[PAYLOAD_SIZE];
  int    bytes;


  if (my_args->m)
    return;


  set_layer(LAYER_APPLICATION);


  display_header_banner("Payload");


  bytes = get_packet_apparentbytesleft(pkt);
  if (bytes <= 0)
    return;
  if (get_packet_bytes(holder, pkt, bytes) == 0)
    return;


  dump_hex_and_text(holder, bytes);

  return;

}
