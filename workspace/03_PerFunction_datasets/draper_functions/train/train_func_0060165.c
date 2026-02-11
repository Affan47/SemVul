_cupsSNMPWrite(
    int            fd,
    http_addr_t    *address,
    int            version,
    const char     *community,
    cups_asn1_t    request_type,
    const unsigned request_id,
    const int      *oid)
{
  int		i;
  cups_snmp_t	packet;
  unsigned char	buffer[CUPS_SNMP_MAX_PACKET];

  int		bytes;
  http_addr_t	temp;


  DEBUG_printf(("4_cupsSNMPWrite(fd=%d, address=%p, version=%d, "
                "community=\"%s\", request_type=%d, request_id=%u, oid=%p)",
		fd, address, version, community, request_type, request_id, oid));

  if (fd < 0 || !address || version != CUPS_SNMP_VERSION_1 || !community ||
      (request_type != CUPS_ASN1_GET_REQUEST &&
       request_type != CUPS_ASN1_GET_NEXT_REQUEST) || request_id < 1 || !oid)
  {
    DEBUG_puts("5_cupsSNMPWrite: Returning 0 (bad arguments)");

    return (0);
  }


  memset(&packet, 0, sizeof(packet));

  packet.version      = version;
  packet.request_type = request_type;
  packet.request_id   = request_id;
  packet.object_type  = CUPS_ASN1_NULL_VALUE;

  strlcpy(packet.community, community, sizeof(packet.community));

  for (i = 0; oid[i] >= 0 && i < (CUPS_SNMP_MAX_OID - 1); i ++)
    packet.object_name[i] = oid[i];
  packet.object_name[i] = -1;

  if (oid[i] >= 0)
  {
    DEBUG_puts("5_cupsSNMPWrite: Returning 0 (OID too big)");

    errno = E2BIG;
    return (0);
  }

  bytes = asn1_encode_snmp(buffer, sizeof(buffer), &packet);

  if (bytes < 0)
  {
    DEBUG_puts("5_cupsSNMPWrite: Returning 0 (request too big)");

    errno = E2BIG;
    return (0);
  }

  asn1_debug("DEBUG: OUT ", buffer, bytes, 0);


  temp = *address;

  _httpAddrSetPort(&temp, CUPS_SNMP_PORT);

  return (sendto(fd, buffer, bytes, 0, (void *)&temp,
                 httpAddrLength(&temp)) == bytes);
}
