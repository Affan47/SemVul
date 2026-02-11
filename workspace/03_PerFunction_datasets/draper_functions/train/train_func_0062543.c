ipmiconsole_check_payload_type (ipmiconsole_ctx_t c, ipmiconsole_packet_type_t p)
{
  uint8_t payload_type, expected_payload_type;
  uint64_t val;

  assert (c);
  assert (c->magic == IPMICONSOLE_CTX_MAGIC);
  assert (IPMICONSOLE_PACKET_TYPE_RESPONSE (p));
  assert (p == IPMICONSOLE_PACKET_TYPE_OPEN_SESSION_RESPONSE
          || p == IPMICONSOLE_PACKET_TYPE_RAKP_MESSAGE_2
          || p == IPMICONSOLE_PACKET_TYPE_RAKP_MESSAGE_4
          || p == IPMICONSOLE_PACKET_TYPE_SET_SESSION_PRIVILEGE_LEVEL_RS
          || p == IPMICONSOLE_PACKET_TYPE_GET_CHANNEL_PAYLOAD_SUPPORT_RS
          || p == IPMICONSOLE_PACKET_TYPE_GET_PAYLOAD_ACTIVATION_STATUS_RS
          || p == IPMICONSOLE_PACKET_TYPE_ACTIVATE_PAYLOAD_RS
          || p == IPMICONSOLE_PACKET_TYPE_SOL_PAYLOAD_DATA_RS
          || p == IPMICONSOLE_PACKET_TYPE_GET_CHANNEL_PAYLOAD_VERSION_RS
          || p == IPMICONSOLE_PACKET_TYPE_DEACTIVATE_PAYLOAD_RS
          || p == IPMICONSOLE_PACKET_TYPE_CLOSE_SESSION_RS);

  if (FIID_OBJ_GET (c->connection.obj_rmcpplus_session_hdr_rs,
                    "payload_type",
                    &val) < 0)
    {
      IPMICONSOLE_CTX_DEBUG (c, ("FIID_OBJ_GET: 'payload_type': %s",
                                 fiid_obj_errormsg (c->connection.obj_rmcpplus_session_hdr_rs)));
      ipmiconsole_ctx_set_errnum (c, IPMICONSOLE_ERR_INTERNAL_ERROR);
      return (-1);
    }
  payload_type = val;

  if (p == IPMICONSOLE_PACKET_TYPE_OPEN_SESSION_RESPONSE)
    expected_payload_type = IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_RESPONSE;
  else if (p == IPMICONSOLE_PACKET_TYPE_RAKP_MESSAGE_2)
    expected_payload_type = IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_2;
  else if (p == IPMICONSOLE_PACKET_TYPE_RAKP_MESSAGE_4)
    expected_payload_type = IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_4;
  else if (p == IPMICONSOLE_PACKET_TYPE_SOL_PAYLOAD_DATA_RS)
    expected_payload_type = IPMI_PAYLOAD_TYPE_SOL;
  else
    expected_payload_type = IPMI_PAYLOAD_TYPE_IPMI;

  if (payload_type != expected_payload_type)
    IPMICONSOLE_CTX_DEBUG (c, ("payload type check failed; p = %d; payload_type = %Xh; expected_payload_type = %Xh", p, payload_type, expected_payload_type));

  return ((payload_type == expected_payload_type) ? 1 : 0);
}
