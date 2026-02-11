ipmiconsole_check_requester_sequence_number (ipmiconsole_ctx_t c, ipmiconsole_packet_type_t p)
{
  uint8_t req_seq, expected_req_seq;
  uint64_t val;

  assert (c);
  assert (c->magic == IPMICONSOLE_CTX_MAGIC);
  assert (IPMICONSOLE_PACKET_TYPE_RESPONSE (p));
  assert (p == IPMICONSOLE_PACKET_TYPE_GET_AUTHENTICATION_CAPABILITIES_RS
          || p == IPMICONSOLE_PACKET_TYPE_SET_SESSION_PRIVILEGE_LEVEL_RS
          || p == IPMICONSOLE_PACKET_TYPE_GET_CHANNEL_PAYLOAD_SUPPORT_RS
          || p == IPMICONSOLE_PACKET_TYPE_GET_PAYLOAD_ACTIVATION_STATUS_RS
          || p == IPMICONSOLE_PACKET_TYPE_ACTIVATE_PAYLOAD_RS
          || p == IPMICONSOLE_PACKET_TYPE_GET_CHANNEL_PAYLOAD_VERSION_RS
          || p == IPMICONSOLE_PACKET_TYPE_DEACTIVATE_PAYLOAD_RS
          || p == IPMICONSOLE_PACKET_TYPE_CLOSE_SESSION_RS);

  if (FIID_OBJ_GET (c->connection.obj_lan_msg_hdr_rs,
                    "rq_seq",
                    &val) < 0)
    {
      IPMICONSOLE_CTX_DEBUG (c, ("FIID_OBJ_GET: 'rq_seq': %s",
                                 fiid_obj_errormsg (c->connection.obj_lan_msg_hdr_rs)));
      ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_INTERNAL_ERROR);
      return (-1);
    }
  req_seq = val;
  expected_req_seq = c->session.requester_sequence_number;

  if (req_seq != expected_req_seq)
    IPMICONSOLE_CTX_DEBUG (c, ("requester sequence number check failed; p = %d; req_seq = %Xh; expected_req_seq = %Xh", p, req_seq, expected_req_seq));

  return ((req_seq == expected_req_seq) ? 1 : 0);
}
