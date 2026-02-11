_send_ipmi_packet (ipmiconsole_ctx_t c, ipmiconsole_packet_type_t p)
{
  uint8_t pkt[IPMICONSOLE_PACKET_BUFLEN];
  int n, pkt_len, dropped = 0;
  struct timeval *t;
  int secure_malloc_flag;

  assert (c);
  assert (c->magic == IPMICONSOLE_CTX_MAGIC);
  assert (IPMICONSOLE_PACKET_TYPE_REQUEST (p));

  secure_malloc_flag = (c->config.engine_flags & IPMICONSOLE_ENGINE_LOCK_MEMORY) ? 1 : 0;

  if (p == IPMICONSOLE_PACKET_TYPE_GET_AUTHENTICATION_CAPABILITIES_RQ
      || p == IPMICONSOLE_PACKET_TYPE_GET_CHANNEL_PAYLOAD_SUPPORT_RQ
      || p == IPMICONSOLE_PACKET_TYPE_GET_PAYLOAD_ACTIVATION_STATUS_RQ
      || p == IPMICONSOLE_PACKET_TYPE_ACTIVATE_PAYLOAD_RQ
      || p == IPMICONSOLE_PACKET_TYPE_GET_CHANNEL_PAYLOAD_VERSION_RQ
      || p == IPMICONSOLE_PACKET_TYPE_DEACTIVATE_PAYLOAD_RQ
      || p == IPMICONSOLE_PACKET_TYPE_CLOSE_SESSION_RQ)
    {
      c->session.requester_sequence_number++;
      if (c->session.requester_sequence_number > IPMI_LAN_REQUESTER_SEQUENCE_NUMBER_MAX)
        c->session.requester_sequence_number = 0;
    }


  if (p == IPMICONSOLE_PACKET_TYPE_OPEN_SESSION_REQUEST
      || p == IPMICONSOLE_PACKET_TYPE_RAKP_MESSAGE_1
      || p == IPMICONSOLE_PACKET_TYPE_RAKP_MESSAGE_3)
    c->session.message_tag++;

  if (p == IPMICONSOLE_PACKET_TYPE_SET_SESSION_PRIVILEGE_LEVEL_RQ
      || p == IPMICONSOLE_PACKET_TYPE_GET_CHANNEL_PAYLOAD_SUPPORT_RQ
      || p == IPMICONSOLE_PACKET_TYPE_GET_PAYLOAD_ACTIVATION_STATUS_RQ
      || p == IPMICONSOLE_PACKET_TYPE_ACTIVATE_PAYLOAD_RQ
      || p == IPMICONSOLE_PACKET_TYPE_GET_CHANNEL_PAYLOAD_VERSION_RQ
      || p == IPMICONSOLE_PACKET_TYPE_DEACTIVATE_PAYLOAD_RQ
      || p == IPMICONSOLE_PACKET_TYPE_CLOSE_SESSION_RQ)
    {

      c->session.session_sequence_number++;
      if (!(c->session.session_sequence_number))
        c->session.session_sequence_number++;
    }

  if ((pkt_len = ipmiconsole_ipmi_packet_assemble (c, p, pkt, IPMICONSOLE_PACKET_BUFLEN)) < 0)
    return (-1);

  if (c->config.debug_flags & IPMICONSOLE_DEBUG_IPMI_PACKETS)
    {
      if (ipmiconsole_packet_dump (c, p, pkt, pkt_len) < 0)
        return (-1);
    }

  if ((n = scbuf_write (c->connection.ipmi_to_bmc, pkt, pkt_len, &dropped, secure_malloc_flag)) < 0)
    {
      IPMICONSOLE_CTX_DEBUG (c, ("scbuf_write: %s", strerror (errno)));
      ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_INTERNAL_ERROR);
      return (-1);
    }

  if (n != pkt_len)
    {
      IPMICONSOLE_CTX_DEBUG (c, ("scbuf_write: invalid bytes written; n=%d; pkt_len=%d", n, pkt_len));
      ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_INTERNAL_ERROR);
      return (-1);
    }

  if (dropped)
    {
      IPMICONSOLE_CTX_DEBUG (c, ("scbuf_write: dropped data: dropped=%d", dropped));
      ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_INTERNAL_ERROR);
      return (-1);
    }

  if (p != IPMICONSOLE_PACKET_TYPE_GET_CHANNEL_PAYLOAD_VERSION_RQ)
    t = &(c->session.last_ipmi_packet_sent);
  else
    t = &(c->session.last_keepalive_packet_sent);

  if (gettimeofday (t, NULL) < 0)
    {
      IPMICONSOLE_CTX_DEBUG (c, ("gettimeofday: %s", strerror (errno)));
      ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_SYSTEM_ERROR);
      return (-1);
    }

  return (0);
}
